/**
 * MovieController
 *
 * @description :: Server-side logic for managing movies
 * @help        :: See http://sailsjs.org/#!/documentation/concepts/Controllers
 */

var get = require('get');
var _ = require('lodash');
var api_key = '67493736c8511d59d83f70c4b88a72f6';
var queryString = require('query-string');
var async = require('async');
var moment = require('moment');

var cacheMovies = function (m, callback) {
	sails.log.debug(m.title)
	var o = {
		imdb_id: m.id,
		release_date: m.release_date,
		synopsis: m.overview,
		title: m.title,
		vote_average: m.vote_average,
		popularity: m.popularity
	};

	if (!!m.backdrop_path) o.backdrop_url = 'http://image.tmdb.org/t/p/w1280/'+m.backdrop_path;
	if (!!m.poster_path) o.poster_url = 'http://image.tmdb.org/t/p/w1280/'+m.poster_path;

	Movie.findOrCreate({imdb_id: m.id}, o).exec(function (err, rec) {
		if (err || !rec || rec.length < 1) {
			sails.log.debug([m.title, 'findOrCreate', err])
			return callback(err);
		}

		// we don't wait for it to finish, we do it asyncly
		fetchCast(rec, function (err, data) {
			if (err) {
				sails.log.debug([m.title, 'fetchCast', err])
				return;
			}
		});

		sails.log.debug([m.title, 'success'])
		return callback(null, rec);
	});
};

var fetchCast = function (m, callback) {
	if (!m) return;
	if (m.cast != null)
		return;
	var query = {
		api_key: api_key
	}
	var url = 'http://api.themoviedb.org/3/movie/'+m.imdb_id+'/credits?'+queryString.stringify(query);
	try
	{
		get(url).asBuffer(function(err, data) {
			if (err) return callback(err, data);
			var cast = JSON.parse(data).cast;
			return Movie.update({imdb_id: m.imdb_id}, {cast: cast}).exec(callback);
		});
	}
	catch (e) { return callback(e); }
};

var sendCachedMovies = function (data, req, res) {
	async.map(
		data.results,
		cacheMovies,
		function (e, movies) {
			if (e) {
				sails.log.debug(['sendCachedMovies', err]);
				return res.json({err:{msg:e}});
			}
			sails.log.debug('sorting by ' + req.param('sortBy'));
			movies = _.chain(movies)
				.sortBy(function (m) {
					// ignore case when sorting by title
					if (req.param('sortBy') == 'title') {
						return _.lowerCase(m.title);
					}
					return m[req.param('sortBy')];
				})
				.pickBy(function (m) {
					if (!m.release_date || !_.isFunction(m.release_date.toISOString))
						return false;
					var date = m.release_date.toISOString().split('-')[0];
					return date >= (req.param('yearFrom') || 1900) && date <= (req.param('yearTo') || 2100);
				})
				.toArray()
				.value();
			sails.log.debug('movies.length = ' + _.size(movies));
			sails.log.debug('order = ' + req.param('order'));
			if (req.param('order') == 'desc')
				return res.json(_.reverse(movies));
			else
				return res.json(movies);
		}
	);
}

module.exports = {
	popular: function (req, res) {
		var query = {
			api_key: api_key,
			query: req.param('name'),
			page: req.param('page') || 1,
			language: req.param('language') || 'en'
		};
		var url = 'http://api.themoviedb.org/3/movie/popular/?'+queryString.stringify(query);
		try
		{
			get(url).asBuffer(function(err, data) {
				if (err) {
					req.session.msg = err;
					return res.redirect('/error');
				}
				return sendCachedMovies(JSON.parse(data), req, res);
			});
		} catch (e) {
			req.session.msg = e;
			return res.redirect('/error');
		}
	},

	search: function (req, res) {
		if (!req.wantsJSON) return res.view();
		else
		{
			var query = {
				api_key: api_key,
				query: req.param('name'),
				page: req.param('page') || 1,
				language: req.param('language') || 'en'
			};
			var url = 'http://api.themoviedb.org/3/search/movie/?'+queryString.stringify(query);
			try
			{
				get(url).asBuffer(function(e, data) {
					sails.log.debug(url)
					if (e) {
						req.session.msg = e;
						return res.json({err:{msg:e}});
					}
					return sendCachedMovies(JSON.parse(data), req, res);
				});
			}
			catch (e) { return res.json({err:{msg:e}}) }
		}
	},

	partial: function (req, res) {
		Movie.findOne({id: req.param('id')}).exec(function (err, movie) {
			if (err || !movie) {
					req.session.msg = err;
					return res.redirect('/error');
			}
			// pretify the date
			movie.release_date = moment(movie.release_date).fromNow();
			// truncate the synopsis
			movie.synopsis = _.truncate(movie.synopsis, { 'length': 140 });
			User.findOne(req.session.user.id, function (err, user) {

				if (err || !user) {
					req.session.msg = err;
					return res.redirect('/error');
				}
				var seen = false;
				if (!!user.movies && _.includes(user.movies, movie.id)) {
					seen = true;
				}
				return res.view({ layout: false, movie: movie, user: user, seen: seen });
			});
		})
	},

	play: function (req, res) {
		async.waterfall(
			[
				function findMovie(cb) {
					Movie.findOne({id: req.param('id')}).exec(cb)
				},
				function findComment(movie, cb) {
					if (!movie.cast || movie.cast == {}) cb('Movie is still under process, try again later');
					return Comment.find({movie_id: movie.id}).populate('user').exec(function (err, comments) {
						return cb(err, movie, comments)
					});
				},
				function findUser(movie, comments, cb) {
					if (!comments) cb('No comments');
					return User.findOne(req.session.user.id).exec(function (err, user) {
						return cb(err, movie, comments, user)
					});
				},
				function seeMovie(movie, comments, user, cb) {
					if (!user) cb('No user');
					user.movies = user.movies || [];
					user.movies.push(movie.id);
					return cb(null, movie, comments, user);
				},
				function saveUser(movie, comments, user, cb) {
					user.save(function (err) {
						return cb(err, { video: movie, comments: comments })
					})
				}
			],
			function (err, result) {
				if (err) {
					sails.log.debug(err)
					req.session.msg = err;
					return res.redirect('/error');
				} else {
					result.video.release_date = moment(result.video.release_date).fromNow(); // pretify the date
					result.video.synopsis = _.truncate(result.video.synopsis, { 'length': 500 }); // truncate the synopsis
					return res.view('movie/play', result);
				}
			})
	},

	add_comment: function(req, res){
		
		Comment.create({comment: req.param('comment'), user: req.session.user.id, movie_id: req.param('id')}).exec(function (err, result){
			if (err || !result || result.length < 1) {
				req.session.msg = "your comment need to be at least 1 chars long";
				return res.redirect('/error');
			}
			return res.redirect('/movie/play/'+req.param('id'));
		})
	}
};
