var express = require('express');
var router = express.Router();
var pool 	= require('../config/connection.js');

  /**
   * Display Account page
  **/
router.get('/', function(req, res) {
	
	var user = {};
	
	// get connection from the pool
	pool.getConnection(function(err, connection) {
		if (err) {
			res.sendStatus(500); return ;
		}
		
		// Get user information to build the profile
		connection.query("SELECT * FROM users WHERE id = ?", [ req.session.user ],  function(err, rows) {
			// Maybe ?
			if (err) {
				res.sendStatus(500); return ;
			}
			
			if (rows[0].picture !== undefined) {
				connection.query("SELECT * FROM images WHERE id = ?", [ rows[0].picture ],  function(error, rows2) {
					// Verify that a picture is found
					if (!error && rows2.length > 0) {
						rows[0].picture = rows2[0].img;
					}
					
					// Render now
					res.render('account', {
						title: 'Account | Matcha',
						user: rows[0],
						connected: req.session.user !== undefined
					});
				});
			} else {
				// Render the page
				res.render('account', {
					title: 'Account | Matcha',
					user: rows[0],
					connected: req.session.user !== undefined
				});
			}
			
			
			
			// Release connection
			connection.release();
		});
	});
});

module.exports = router;