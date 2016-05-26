var express = require('express');
var router 	= express.Router();
var async 	= require('async');
var pool 	= require('../config/connection.js');
var events	= require('../config/event');
var moment	= require('moment');

// Register reporting route
router.post('/report', function( req, res ) {
	 var id = req.body.id, reason = req.body.reason;
	 
	 // verify the data
	 if (id == undefined || reason == undefined || id === req.session.user) {
		 res.sendStatus( 400 ); return ;
	 }
	 
	 // get connection from pool
	 pool.getConnection(function( err, connection ) {
		if ( err ) { res.sendStatus( 500 ); return ; }
		
		// Generate an uuid
		var uuid = 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function(c) {
			var r = Math.random()*16|0, v = c == 'x' ? r : (r&0x3|0x8);
			return v.toString(16);
		});
		
		// verify that the user reported exist
		connection.query("SELECT id FROM users WHERE id = ?", [ id ], function (err, rows) {
			if (rows.length == 0)
				res.sendStatus( 404 );
			else {
				// create the report
				connection.query("INSERT INTO reports (id, user, reported, type) VALUES (?, ?, ?, ?)", 
					[uuid, req.session.user, id, reason], function( err, rows) {
					if ( err )
						res.sendStatus( 500 );
					else
						res.sendStatus( 201 );
				});
			}
			connection.release();
		});
	 });
});

// Register blocking route
router.post('/block', function( req, res ) {
	 var id = req.body.id;
	 
	 // verify the data
	 if (id == undefined || id === req.session.user) {
		 res.sendStatus( 400 ); return ;
	 }
	 
	 // get connection from pool
	 pool.getConnection(function( err, connection ) {
		if ( err ) { res.sendStatus( 500 ); return ; }
		
		// Generate an uuid
		var uuid = 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function(c) {
			var r = Math.random()*16|0, v = c == 'x' ? r : (r&0x3|0x8);
			return v.toString(16);
		});
		
		// verify that the user reported exist
		connection.query("SELECT * FROM user_blockeds WHERE user = ? AND blocked = ?", [ req.session.user, id ], function (err, rows) {
			// block this user
			if (rows.length == 0) {
				connection.query("INSERT INTO user_blockeds (user, blocked) VALUES (?, ?)",  [req.session.user, id], function( err, rows) {
					if ( err )
						res.sendStatus( 500 );
					else
						res.sendStatus( 201 );
				});
			}
			// unblock him
			else {
				// insert in database
				connection.query("DELETE FROM user_blockeds WHERE user = ? AND blocked = ?",  [req.session.user, id], function( err, rows) {
					if ( err )
						res.sendStatus( 500 );
					else
						res.sendStatus( 201 );
				});
			}
			connection.release();
		});
	 });
});

// Register match route
router.post('/match', function( req, res ) {
	 var id = req.body.id;
	 
	 // verify the data
	 if (id == undefined || id === req.session.user) {
		 res.sendStatus( 400 ); return ;
	 }
	 
	 // get connection from pool
	 pool.getConnection(function( err, connection ) {
		if ( err ) { res.sendStatus( 500 ); return ; }
		
		// verify if the user has already match the user or not
		connection.query("SELECT * FROM user_matchs WHERE user = ? AND matched = ?", [ req.session.user, id ], function (err, rows) {
			// match this user
			if (rows.length == 0) {
				connection.query("INSERT INTO user_matchs (user, matched) VALUES (?, ?)",  [req.session.user, id], function( err, rows) {
					if ( err )
						res.sendStatus( 500 );
					else {
						res.sendStatus( 201 );
						events.emit('user_match', req.session.user, id);
					}
				});
			}
			// un match him
			else {
				// insert in database
				connection.query("DELETE FROM user_matchs WHERE user = ? AND matched = ?",  [req.session.user, id], function( err, rows) {
					if ( err )
						res.sendStatus( 500 );
					else {
						res.sendStatus( 201 );
						events.emit('user_unmatch', req.session.user, id);
					}
				});
			}
			connection.release();
		});
	 });
});


// Register getting visits route
router.post('/visit', function( req, res ) {
	 var id = req.body.id;
	 
	 // verify the data
	 if (id == undefined) {
		 res.sendStatus( 400 ); return ;
	 }
	 
	 // get connection from pool
	 pool.getConnection(function( err, connection ) {
		if ( err ) { res.sendStatus( 500 ); return ; }
		
		var sql = connection.query("SELECT * FROM visits WHERE visited = ? ORDER BY 'date' DESC LIMIT 15", [ id ], function (err, rows) {
			async.each(rows, function (item, callback) {
				// get the user name
				connection.query("SELECT * FROM users WHERE id = ?", [ item.user ],  function( err, rows ) {
					if (err) { callback( true ); return ; }
					
					// set the user name and the date		
					item.user = rows[0].firstname + " " + rows[0].lastname;
					item.date = moment(item.date).fromNow();
					callback();
				});
			}, function ( err ) {
				if ( err )
					res.sendStatus( 500 );
				else 
					res.send(rows);
			});
		});
		console.log(sql.sql);
		connection.release();
	 });
});

module.exports = router;