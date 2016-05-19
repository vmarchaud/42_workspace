var express = require('express');
var router 	= express.Router();
var async 	= require('async');
var pool 	= require('../config/connection.js');


// Register search user by name route
router.post('/byName', function( req, res ) {
	 var input = req.body.input;
	 
	 // is request correctly formed
	 if (input == undefined || input.length == 0) {
	 	res.sendStatus( 400 ); return ;
	 }
	 
	 input = "%" + input + "%";
	 
	 // get connection from the pool
	 pool.getConnection(function( err, connection ) {
		if ( err ) { res.sendStatus( 500 ); return ; }
	    
	  	// delete image
		connection.query("SELECT id,firstname,lastname,picture FROM users WHERE firstname LIKE ? OR lastname LIKE ?"
			, [ input, input ], function ( err, rows ) {
			if (err || rows.length == 0) {
				console.log(err);
				connection.release();
		  		res.sendStatus( 404 );
			} else {
				var users = [];
				async.each(rows, function (item, callback) {
					// if the user has no picture, send it like this
					if (item.picture == undefined || item.picture.length == 0) {
						users.push( rows[0] );
						callback();
					}
					// else query the image and send it with it
					else {
						connection.query("SELECT * FROM images WHERE id = ?", [ item.picture ],  function( err, rows ) {
							if (err) { connection.release(); callback( true ); return ; }
									
							// image found
							if ( rows.length > 0 ) {
								// replace it the user obj and push into the array
								item.picture = rows[0].img;
								users.push( item );
							}
							// in all case call the callback
							callback();
						});
					}
				}, function (err) {
					connection.release();
					if (err) {
						res.sendStatus( 404 );
					}
					res.send( users );
				});
			}
		});
	});
});

module.exports = router;