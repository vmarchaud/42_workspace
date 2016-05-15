var express = require('express');
var router = express.Router();
var async = require('async');
var pool 	= require('../config/connection.js');
var http = require('http');

  /**
   * Display Account page
  **/
router.get('/', function( req, res ) {
	
	// make paralel request to get tags AND get user data + profile picture + all image
	async.parallel([
		
		function( callback ) {
			pool.getConnection(function( err, connection ) {
				if ( err ) { 	callback( true ); return ; }
				
				// Get information to build the user data
				connection.query("SELECT * FROM users WHERE id = ?", [ req.session.user ],  function( err, rows ) {
					if (err) { connection.release(); callback( true ); return ; }
					
					if (rows[0].picture !== undefined) {
						// if he has a profile picture
						connection.query("SELECT * FROM images WHERE id = ?", [ rows[0].picture ],  function( error, rows2 ) {
							// Verify that the picture is found
							if (!error && rows2.length > 0) {
								rows[0].picture = rows2[0].img;
								
								// we have the image, this call is finish
								connection.release();
								callback( false, rows[0] );
							}
						});
					}
					else {
						// he doesnt have image so the call is finish here
						connection.release();
						callback( false, rows[0] );
					}
				});
			});
		},
		
		function( callback ) {
			pool.getConnection(function( err, connection ) {
				if ( err ) { callback( true ); return ; }
				
				// Get user tag 
				connection.query("SELECT * FROM user_tags WHERE user = ?", [ req.session.user ],  function( err, rows ) {
					if (err) { connection.release(); callback( true ); return ; }
					
					var tags = [];
					
					if ( rows.length > 0 ) {
						// if he has some tags, get them
						async.each(rows, function (item, callback) {
							connection.query("SELECT * FROM tags WHERE id = ?", [ item.tag ],  function( err, rows2 ) {
								if (err) { console.log(err); connection.release(); callback( true ); return ; }
								
								// if the tag is found on the list
								if ( rows2.length > 0 ) {
									// push it into the global array
									tags.push( { id: rows2[0].id, name: rows2[0].name } );
									callback();
								}
							});
						}, function (err) {
							// release conenction
							connection.release();
							
							if ( err )
								callback( true );
							else
								callback( false, tags );
						});
					}
					else {
						// this call is finish here cause the user doesnt have any tag
						connection.release();
						callback( false, tags );
					}
				});
			});
		},
		// Get the user image's
		function( callback ) {
			pool.getConnection(function( err, connection ) {
				if ( err ) { 	callback( true ); return ; }
				
				// Get information to build the user data
				connection.query("SELECT * FROM images WHERE user = ?", [ req.session.user ],  function( err, rows ) {
					if (err) { connection.release(); callback( true ); return ; }
					
					connection.release();
					callback( false, rows );
				});
			});
		}
	],
 	// the callback function that will be called when both request has been done
  	function( err, results ) {
		// if there is an error
    	if( err ) { res.send(500); return; }
		
		// else render the page
		res.render('account', {
			title: 'Account | Matcha',
			user: results[0],
			tags: results[1],
			images: results[2],
			connected: req.session.user !== undefined
		});
  	}
  );
});

// Register update route
router.post('/update', function( req, res ) {
	 var type = req.body.type, data = req.body.data;
	 
	 // is request correctly formed
	 if (type == undefined || data == undefined) {
	 	res.sendStatus( 400 ); return ;
	 }
	 
	 
	 async.series([
		function(callback) { 
			// for the location we will need to check if he refused
			if (type === "location" && data === "refused" && req.ip != "::1" && req.ip != "127.0.0.1") {
				var request = http.get("http://ipinfo.io/" + req.ip + "/loc", function(res) {
					// Buffer the body entirely for processing as a whole.
					var bodyChunks = [];
					res.on('data', function(chunk) {
						bodyChunks.push(chunk);
					}).on('end', function() {
						var body = Buffer.concat(bodyChunks);
						data = body;
						callback(null, 1);
					})
				});
			} 
			else
				callback(null, 1);
			
		 },
		function(callback) { 
			// get connection from the pool
			pool.getConnection(function( err, connection ) {
				if (err) {
					res.sendStatus( 500 ); callback(null, 2); return ;
				}
				// Make the request to update the data
				connection.query("UPDATE users SET ??=? WHERE id = ?",  [ type, data, req.session.user ],  function(err, rows) {
					// If there is an error (ex : attribute doesnt not exist)
					if (err) {
						res.sendStatus( 400 );
						connection.release();
					}
					// Else its good
					else {
						connection.release();
						res.sendStatus( 200 );
					}
					callback(null, 2);
				})
			});
			
		 }
	]);
});

// Register retreive route
router.post('/retrieve', function( req, res ) {
	 var type = req.body.type;
	 
	 // is request correctly formed
	 if (type == undefined) {
	 	res.sendStatus( 400 ); return ;
	 }
	 // get connection from the pool
	 pool.getConnection(function( err, connection ) {
	   if (err) {
		  res.sendStatus( 500 ); return ;
	   }
	   // Make the request to update the data
	   connection.query("SELECT ?? FROM users WHERE id = ?",  [ type, req.session.user ],  function(err, rows) {
		  // If there is an error (ex : attribute doesnt not exist)
			if (err) 
				res.sendStatus( 400 );
		  	else if (rows[0][type].length == 0) 
				res.sendStatus( 400 );
		  	else 
				res.send( rows[0] );
		 	connection.release();
		});
	});
});

// Register any tag update
router.post('/tag/add', function( req, res ) {
	 var tag = req.body.tag;
	 
	 // is request correctly formed
	 if ( tag == undefined ) {
	 	res.sendStatus( 400 ); return ;
	 }
	 
	 // get connection from the pool
	 pool.getConnection(function( err, connection ) {
		if ( err ) { res.sendStatus( 500 ); return ; }
	   
	  	// tag name already exist ?
		connection.query("SELECT * from tags WHERE name LIKE ?",  [ tag ],  function( err, rows ) {
			var id = null;
			
			// if not
			if (rows.length == 0) {
				// Generate an uuid
				id = 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function(c) {
					var r = Math.random()*16|0, v = c == 'x' ? r : (r&0x3|0x8);
					return v.toString(16);
				});
				
				// Create it
				connection.query("INSERT INTO tags (id, name) VALUES( ?, ? )", [ id, tag ], function ( err, rows ) {});
			} 
			// else just get the id 
			else 
				id = rows[0].id;
			
			// verify that the doesnt have the tag already
			connection.query("SELECT * FROM user_tags WHERE user = ? AND tag = ?", [ req.session.user, id ], function ( err, rows ) {
				if (rows.length == 0) {
					// now register it to the user
					connection.query("INSERT INTO user_tags (user, tag) VALUES( ?, ? )", [ req.session.user , id ], function ( err, rows ) {});
					connection.release();
		  			res.sendStatus( 201 );
				}
				// else tell him that he already has this one 
				else {
					connection.release();
		  			res.sendStatus( 409 );
				}
			});
		});
	});
});

// Register any tag update
router.post('/tag/delete', function( req, res ) {
	 var id = req.body.tag;
	 
	 // is request correctly formed
	 if ( id == undefined ) {
	 	res.sendStatus( 400 ); return ;
	 }
	 
	 // get connection from the pool
	 pool.getConnection(function( err, connection ) {
		if ( err ) { res.sendStatus( 500 ); return ; }
	   
	  	// delete the tag from the user
		connection.query("DELETE FROM user_tags WHERE tag = ? AND user = ?",  [ id, req.session.user ],  function( err, rows ) {
			if ( err ) {
				connection.release();
				res.sendStatus( 400 );
			}
		});
		
		connection.release();
		res.sendStatus( 200 );
	});
});

module.exports = router;