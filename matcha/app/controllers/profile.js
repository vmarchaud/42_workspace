var express 	= require('express');
var router 		= express.Router();
var async 		= require('async');
var pool 		= require('../config/connection.js');
var http 		= require('http');
var moment 		= require('moment');

  /**
   * Display Account page
  **/
router.get('/:id', function( req, res ) {
	var user = req.params.id;
	
	// make paralel request to get tags AND get user data + profile picture + all image
	async.parallel([
		
		function( callback ) {
			pool.getConnection(function( err, connection ) {
				if ( err ) { 	callback( true ); return ; }
				
				// Get information to build the user data
				connection.query("SELECT * FROM users WHERE id = ?", [ user ],  function( err, rows ) {
					if (err || rows.length == 0) { connection.release(); callback( true ); return ; }
					
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
                            else {
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
				connection.query("SELECT * FROM user_tags WHERE user = ?", [ user ],  function( err, rows ) {
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
				connection.query("SELECT * FROM images WHERE user = ?", [ user ],  function( err, rows ) {
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
    	if( err ) { res.sendStatus(500); return; }
		
		// update the date for a cool render
		results[0].last_visit = moment(results[0].last_visit).fromNow();
		
		// else render the page
		res.render('profile', {
			title: results[0].firstname + "'s profile | Matcha",
			user: results[0],
			tags: results[1],
			images: results[2],
			connected: req.session.user !== undefined
		});
  	}
  );
});


module.exports = router;