var events	= require('../config/event');
var async 	= require('async');
var pool 	= require('../config/connection.js');

module.exports = function (users) {
	// listen match event
	
	events.on('user_match', function (user, matched) {
		
		// get connection from pool
		pool.getConnection(function( err, connection ) {
			if ( err ) { return ; }
			
			connection.query("SELECT * FROM user_matchs WHERE user = ? AND matched = ?", [ matched, user ], function (err, rows) {
				// if user matched him that matched him earlier
				if (rows.length > 0) {
					// update to say its mutual
					connection.query("UPDATE user_matchs SET mutual = '1' WHERE matched = ? AND user = ?", [ user, matched ], function (err, rows) {});
					connection.query("UPDATE user_matchs SET mutual = '1' WHERE matched = ? AND user = ?", [ matched, user ], function (err, rows) {});
					
					// and notifiate the matched
					if (users[matched] != undefined) 
						users[matched].emit('new_alerts');
					
					// generate a alert id	
					var id = 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function(c) {
						var r = Math.random()*16|0, v = c == 'x' ? r : (r&0x3|0x8);
						return v.toString(16);
					});
					// get his name
					connection.query("SELECT firstname,lastname FROM users WHERE id = ?", [ user ], function (err, rows) {
						var msg = rows[0].firstname + " " + rows[0].lastname + " has matched you back";
						// and register the alert
						connection.query("INSERT INTO user_alerts (id, user, msg) VALUES (?, ?, ?)", [id, matched, msg], function(err, rows) {});
					});
				}
			});
			connection.release();
		});
	});
	
	
	// listen unmatch event
	events.on('user_unmatch', function (user, unmatched) {
		// get connection from pool
		pool.getConnection(function( err, connection ) {
			if ( err ) { return ; }
			
			connection.query("SELECT * FROM user_matchs WHERE user = ? AND matched = ?", [ unmatched, user ], function (err, rows) {
				// if the matched match him
				if (rows.length > 0) {
					// update to say its not mutual
					connection.query("UPDATE user_matchs SET mutual = '0' WHERE matched = ? AND user = ?", [ user, unmatched ], function (err, rows) {});
					
					// and notifiate the matched
					if (users[unmatched] != undefined) 
						users[unmatched].emit('new_alerts');
					
					// generate a alert id	
					var id = 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function(c) {
						var r = Math.random()*16|0, v = c == 'x' ? r : (r&0x3|0x8);
						return v.toString(16);
					});
					
					// get his name
					connection.query("SELECT firstname,lastname FROM users WHERE id = ?", [ user ], function (err, rows) {
						var msg = rows[0].firstname + " " + rows[0].lastname + " no longer match you";
						// and register the alert
						connection.query("INSERT INTO user_alerts (id, user, msg) VALUES (?, ?, ?)", [id, unmatched, msg], function(err, rows) {});
					});
				}
			});
			connection.release();
		});
	});
	
	// listen on visit event
	events.on('user_visit', function (user, visited) {
		
		// get connection from pool
		pool.getConnection(function( err, connection ) {
			if ( err ) { return ; }
			
			// get user name for alert
			connection.query("SELECT * FROM users WHERE id = ?", [ user ], function (err, rows) {
				// generate an id
				var uuid = 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function(c) {
					var r = Math.random()*16|0, v = c == 'x' ? r : (r&0x3|0x8);
					return v.toString(16);
				});
				// create the msg
				var msg = rows[0].firstname + " " + rows[0].lastname + " has visited your profile";
				// create the alert
				connection.query("INSERT INTO user_alerts (id,user,msg) VALUES (?, ?, ?)", [ uuid, visited, msg ], function (err, rows) {});
			});
			
			connection.release();
		});
	});
}