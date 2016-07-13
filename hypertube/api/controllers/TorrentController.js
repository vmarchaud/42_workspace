/**
 * TorrentController
 *
 * @description :: Server-side logic for managing Torrents
 * @help        :: See http://sailsjs.org/#!/documentation/concepts/Controllers
 */

const _             = require('lodash')
const fs            = require("fs-extra");
const torrentStream = require('torrent-stream');
const throttle      = require('throttle');
const ffmpeg        = require('fluent-ffmpeg');
const pump          = require('pump');

var mimeTypes = {
	"f4v":		"video/mp4",
	"f4p":		"video/mp4",
	"mp4":		"video/mp4",
	"mkv":		"video/webm", // will be converted into webm
	"avi":		"video/webm",  // will be converted into webm
	"mpa":		"video/mpeg",
	"mpe":		"video/mpeg",
	"mpeg":		"video/mpeg",
	"mpg":		"video/mpeg",
	"mpv2":		"video/mpeg",
	"mp2":		"video/mpeg",
	"webm":		"video/webm",
	"ogg":		"video/ogg",
    "wmv":      "video/webm" // will be converted into webm
};

var mimeToConvert = {
    "wmv" : "webm",
    "avi" : "webm",
    "mkv" : "webm"
}

// used to store the engine already running to download file
var engines = {};

module.exports = {
    /**
    *   `TorrentController.search()`
    *   /torrent/search/:name
    *
    *   Route used to search for a torrent, it will search in the database if its already here or start crawling it
    */
    search: function (req, res) {

        var name = req.params.name;
		sails.log.debug("TorrentController | search |  searching for : " + name);

        // ensure that the name is valid
        if (name === undefined || name.length == 0)
            return res.status(400);

		Movie.find({ title: name }).populate('torrent').exec(function ( err, results ) {
			if (err !== undefined && results.length > 0 ) {
				var movie = results[0];

				// if the torrent for this movie is already found
				if (movie.torrent !== null && movie.torrent !== undefined) {
					sails.log.debug("TorrentController | search |  A torrent has been found for title " + name )
               		return res.ok(movie.torrent);
				} else {
					// else search for it
					sails.log.debug("TorrentController | search |  No torrent found for title " + name + " start crawling ...")

					CrawlerService.search(name, function ( err, result ) {
						// if nothing is found send no result
						if ( err || result == null) {
							res.notFound(); return ;
						}

						// set the title to search it next time
						result.title = result.info.title;
						result.download = false;
							
						// and register it in the database
						Torrent.create(result, function(err, model) {
							if (err) 
								return res.serverError(err);
							else {
								sails.log.debug("TorrentController | search |  Crawler has found a torrent for movie " + movie.id + ", registering it under id " + model.id);
								res.ok(model.toJSON());
								// link with movie
								movie.torrent = model;
								movie.save();
							}
						});
					});
				}
			}
			else
				res.notFound();
		});
    },

    /**
    *   `TorrentController.download()`
    *   /torrent/:id/download
    *
    *   Route used to start the download of a torrent that has been prevsiouly crawled
    */
    download: function (req, res) {
        Torrent.find({ id: req.params.id }).exec(function ( err, results ) {
             // check if we found the torrent to start the download
             if ( err || results.length == 0) {
                 res.notFound();
             } else {
                var torrent = results[0];

                // if the torrent is already downloaded
                if (torrent.download) 
                   return res.json(torrent.toJSON());
                
                // if the engine is already downloading the torrent
				else if (engines[torrent.id] !== undefined) 
					return res.ok(torrent.toJSON());
				

                 // start the download
                var engine = torrentStream(torrent.magnet);

				// try to find EN subtitles for this torrent
				var subtitle = SubtitleService.search(torrent, "en", function ( err, results) {
                    if (err) {
						sails.log.debug("TorrentController | subtitle | no EN subtitle found for torrent " + torrent.id);
						sails.log.debug(JSON.stringify(err));
					} else
						sails.log.debug("TorrentController | subtitle | EN subtitle found for torrent " + torrent.id);
                });

                engine.on('ready', function() {    
                    var target = null;

                    // find the video that interest us
                    async.each(engine.files, function( file, callback ) {
                        // get the extention
                        var ext = file.name.split(".").pop();

                        // if the file is not video or its a sample
                        if (mimeTypes[ext] === -1 || file.name.indexOf("sample") !== -1) {
                            callback()
                            return ;
                        }

                        // if we didnt have yet found video, set this one and continue
                        if (target == null) 
                            target = file;
                        // if the file is bigger that the one already get, get this one
                        else if (file.length > target.length) {
                            target = file;
                        }

                        callback();
                    }, function( err ) {

                        sails.log.debug("TorrentController | download | File choosen for torrent " + torrent.id + " is " + target.name);

                        var stream = target.createReadStream();
                        var path = process.cwd() + '/.tmp/private/videos/' + torrent.id + '/';

                        // store the torrent instance
                        engines[torrent.id] = target;

                        // make the folders that will receive the torrent file
                        fs.mkdirs(path, function (err) {
                            if (err)
                                res.serverError(err);
                            else {
								var ext = target.name.split('.').pop();

                                // update with the torrent path
								torrent.path = '/videos/' + torrent.id + '/' + target.name;
                                torrent.size = target.length;
								torrent.mime = mimeTypes[ext];
                                torrent.save();
                                
                                // send the model with the path
                                res.ok(torrent.toJSON());

                                var writer = fs.createWriteStream(path + '/' + target.name);
								
								// transcode if its mkv
								if (mimeToConvert[ext] !== undefined) {
                                    ffmpeg(stream).videoCodec('libvpx').audioCodec('libvorbis').format('webm')
                                    .audioBitrate(128)
                                    .videoBitrate(1024)
                                    .outputOptions([
                                        '-deadline realtime',
                                        '-error-resilient 1'
                                    ])
                                    .on('end', function () {
                                        sails.log.debug("TorrentController | download | Download of torrent " + torrent.id + " is finished");
                                        torrent.download = true;
                                        
										torrent.size = fs.statSync(path + '/' + target.name).size;
                                        fs.rename(path + '/' + target.name, path + '/' + target.name.replace(ext, mimeToConvert[ext]));
                                        torrent.path = torrent.path.replace(ext, mimeToConvert[ext]);
                                        torrent.save();
                                    })
									.on('error', function (err) {
										sails.log.debug("cant convert the movie");
										sails.log.debug(err);
									})
                                    .save(path + '/' + target.name);
                                }
								else {
                                    pump(stream, writer);
                                    stream.on('end', function () {
                                        sails.log.debug("TorrentController | download | Download of torrent " + torrent.id + " is finished");
                                        torrent.download = true;
                                        torrent.save();
                                    });
                                }
									
                                
                               
                            }
                        });
                    });
                });
             }
        });
    },

    /**
    *   `TorrentController.stream()`
    *   /torrent/:id/stream
    *
    *   Route used to start the download of a torrent that has been prevsiouly crawled
    */
    stream: function (req, res) {
        Torrent.find({ id: req.params.id }).exec(function ( err, results ) {
            // check if we found the torrent to start the download
            if ( err || results.length == 0) {
                return res.notFound();
            }
            // if the torrent is not already download, get the engine stream
            else if (!results[0].download) {
                var torrent = results[0];
                sails.log.debug("TorrentController | stream | Streaming torrent " + torrent.id + " directly from stream");

                if (engines[torrent.id] === undefined) {
                    return res.json({ err: "please start the download before ask for a stream" });
                } else {
					var ext = torrent.path.split('.').pop();

                    if (req.headers['range']) {
                        var parts = req.headers.range.replace(/bytes=/, "").split("-");

                        var start = parseInt(parts[0], 10);
                        var end = torrent.size - 1;
                        var chunksize = ( end - start ) + 1;

                        var file = engines[torrent.id].createReadStream({start: start, end: end});

                        res.writeHead(206, { 
                            'Content-Range': 'bytes ' + start + '-' + end + '/' + torrent.size, 
                            'Accept-Ranges': 'bytes', 
                            'Content-Length': chunksize,
                            'Content-Type': torrent.mime
                        });

                         // if mkv just wait for the conversion
                        if (mimeToConvert[ext] !== undefined) {
                            var convert = ffmpeg(file).videoCodec('libvpx').audioCodec('libvorbis').format('webm')
                                    .audioBitrate(128)
                                    .videoBitrate(1024)
                                    .outputOptions([
                                        '-threads 8',
                                        '-deadline realtime',
                                        '-error-resilient 1'
                                    ])
									.on('error', function (err) {
										sails.log.debug("cant convert the movie");
										sails.log.debug(err);
									})
                            pump(convert, res);
                        }
                        else
						    pump(convert, res);
                    } else {
                        res.writeHead(200, { 'Content-Length': torrent.size, 'Content-Type': torrent.mime });
						pump(engines[torrent.id].createReadStream(), res);
                    }
                }

             } 
             // if the file is download, just stream the content
             else {
                var torrent = results[0];
                sails.log.debug("TorrentController | stream | Streaming torrent " + torrent.id + " from cached file");

                var path = process.cwd() + '/.tmp/private' + torrent.path;

                if (req.headers['range']) {
                    var parts = req.headers.range.replace(/bytes=/, "").split("-");

                    var start = parseInt(parts[0], 10);
                    var end = torrent.size - 1;
                    var chunksize = (end-start)+1;

                    var file = fs.createReadStream(path, {start: start, end: end});

                    res.writeHead(206, { 
                        'Content-Range': 'bytes ' + start + '-' + end + '/' + torrent.size, 
                        'Accept-Ranges': 'bytes', 
                        'Content-Length': chunksize, 
                        'Content-Type': torrent.mime
                    });
                    pump(file, res);
                } else {
                    res.writeHead(200, { 'Content-Length': torrent.size, 'Content-Type': torrent.mime });
                    pump(fs.createReadStream(path), res);
					// update model to know last date when torrent has been viewed
					torrent.updatedAt = Date.now();
					torrent.save();
                }
             }
        });
    }

};

