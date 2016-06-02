var express = require('express');
var router 	= express.Router();
var async 	= require('async');
var pool 	= require('../config/connection.js');


// display suggest page
router.get('/', function(req, res) {
	pool.getConnection(function(err, connection) {
			if (err) { res.sendStatus( 500 ); return ; }
			
			connection.query('SELECT * FROM tags', function (err, rows) {
				res.render('suggest', {
					title: 'Suggest | Matcha',
					connected: req.session.user !== undefined,
					userName: (req.user) ? req.user.username : undefined,
					tags: rows
				});
				connection.release();
			});
		});
	
});

// function used to calculate the distance betwwen two location
function distance(loc, loc1) {
	var loc2 = loc.split(','), loc3 = loc1.split(',');
	var lat1 = loc2[0], lon1 = loc2[1], lat2 = loc3[0], lon2 = loc3[1];
	var p = 0.017453292519943295, c = Math.cos;
	var a = 0.5 - c((lat2 - lat1) * p)/2 +  c(lat1 * p) * c(lat2 * p) *  (1 - c((lon2 - lon1) * p))/2;
	return 12742 * Math.asin(Math.sqrt(a));
}

// used to clear array
Array.prototype.clean = function(deleteValue) {
  for (var i = 0; i < this.length; i++) {
    if (this[i] == deleteValue) {         
      this.splice(i, 1);
      i--;
    }
  }
  return this;
};


// Register search user by name route
router.post('/', function( req, res ) {
	var age_min = req.body.age_min, age_max = req.body.age_max;
	var distance_min = req.body.distance_min, distance_max = req.body.distance_min;
	var score_min = req.body.score_min, score_max = req.body.score_max;
	var interests = req.body.interests || [];
	 
	// is request correctly formed
	if (age_min == undefined || age_max === undefined || distance_min == undefined || distance_max == undefined
	 	|| score_min === undefined || score_max === undefined || interests === undefined) {
		res.sendStatus( 400 ); return ;
	}
	 
	// get connection from the pool
	pool.getConnection(function( err, connection ) {
		if ( err ) { res.sendStatus( 500 ); return ; }
			// get user data to compare
			connection.query('SELECT * FROM users WHERE id = ?', [ req.session.user ], function (err, rows) {
				var requester = rows[0];
				var sql = "1";
				// if the user is hetero men find a hetero/bi women
				if (requester.orientation === "HETEROSEXUAL" && requester.gender === "MEN")
					sql = "gender = 'WOMEN' AND orientation != 'HOMOSEXUAL'";
				// if the user is hetero and women find an hetero/bi men
				else if (requester.orientation === "HETEROSEXUAL" && requester.gender === "WOMEN")
					sql = "gender = 'MEN' AND orientation != 'HOMOSEXUAL'";
				// if the user is homo, get same gender bi or homo
				else if (requester.orientation === "HOMOSEXUAL")
					sql = "gender = '" + requester.gender + "' AND orientation != 'HETEROSEXUAL'";
				// if his bi, just get everyone except oposed sex homo
				else if (requester.orientation === "BISEXUAL" && requester.gender == "MEN")
					sql = "id NOT IN (SELECT id FROM `users` WHERE `gender` = 'WOMEN' AND orientation = 'HOMOSEXUAL')";
				// if his bi, just get everyone except oposed sex homo
				else if (requester.orientation === "BISEXUAL" && requester.gender == "WOMEN")
					sql = "id NOT IN (SELECT id FROM `users` WHERE `gender` = 'MEN' AND orientation = 'HOMOSEXUAL')";
				
				// get users that match preset with gender and orientation
				connection.query('SELECT * FROM users WHERE ' + sql + ' ORDER BY score DESC', [], function ( err, users ) {
					console.log('SELECT * FROM users WHERE ' + sql + ' ORDER BY score DESC');
					async.each(users, function(user, callback) {
						// if its the requester ignore
						if (user.id === requester.id) {
							delete users[users.indexOf(user)];
							callback();
						}
						// empty user that doesnt match distance
						else if ( user.location.length == 0 || distance(requester.location, user.location) < distance_min ||
							distance(requester.location, user.location) > distance_max) {
							delete users[users.indexOf(user)];
							callback();
						} 
						// empty user that doesnt match score
						else if ( user.score < score_min || user.score > score_max) {
							delete users[users.indexOf(user)];
							callback();
						}
						// empty user that doesnt match age
						else if ( user.age < age_min || user.age > age_max) {
							delete users[users.indexOf(user)];
							callback();
						}
						// if the user choose interest, match them
						else if ( interests.length > 0) {
							connection.query('SELECT * FROM `user_tags` WHERE `user` = ? AND `tag` IN (?)', [ user.id, interests.join(',') ], 
								function ( err, rows) {
								if (rows.length == 0)
									delete users[users.indexOf(user)];
								callback();
							})
						} else {
							callback();
						}
					}, function ( err ) {
						var returned_users = [];
						users.clean();
						
						// if there is no one already just send him a empty array
						if (users.length == 0) {
							connection.release();
							res.send( returned_users );
							return ;
						}
						
						// get the picture and name from all users that are still here
						async.each(users, function (item, callback) {
							// if the user has no picture, send it like this
							if (item.picture == undefined || item.picture.length == 0) {
								returned_users.push( item );
								callback();
							}
							// else query the image and send it with it
							else {
								connection.query("SELECT * FROM images WHERE id = ?", [ item.picture ],  function( err, rows ) {
									if (err) { returned_users.push( item ); callback( true ); return ; }
											
									// image found
									if ( rows.length > 0 ) {
										// replace it the user obj and push into the array
										item.picture = rows[0].img;
										returned_users.push( item );
									}
									// in all case call the callback
									callback();
								});
							}
						}, function (err) {
							// sort user to put interesting one on top of list
							async.sortBy(returned_users, function(user, callback) {
								// compute nbr of common interests of user and requester
								connection.query('SELECT DISTINCT * FROM `user_tags` WHERE user = ? AND tag IN ( SELECT tag FROM `user_tags` WHERE user = ?)',
									[ user.id, requester.id], function ( err, rows) {
									// ponderate with -(distance / 2) + (nbr interets * 20) + (score / 12)
									 callback(null, (-(distance(user.location, requester.location) / 2) + (rows.length * 20) + (user.score / 12)) * - 1);
								});
							}, function(err, result){
								// we have our sorted user sorted by interest in common
								returned_users = result;
							});
							
							
							if (err) {
								res.sendStatus( 404 );
							}
							res.send( returned_users );
							connection.release();
						});
					});
				});
			})
	});
});

module.exports = router;