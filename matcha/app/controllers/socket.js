var pool 		= require('../config/connection.js');
var http 		= require('http');
var moment 		= require('moment');
var async		= require('async');

module.exports = function(io, users) {
  // register websocket 
	io.on('connection', function (socket) {
		
		var id = socket.handshake.session.user;
		// if the user is connected
		if (id != undefined) {
			
			// store the user socket
			users[id] = socket;
			
			// get sql connection
			pool.getConnection(function (err, connection) {
				if ( err ) { return ; }
				
				// send him the nbr alert unread
				connection.query("SELECT COUNT(*) FROM user_alerts WHERE user = ? AND shown = '0'", [id], function(err, rows) {
					socket.emit('alerts', { 'nbr': rows[0]['COUNT(*)'] });
				});
				
				
				// put him online
				connection.query("UPDATE users SET last_visit=? WHERE id = ?", [ '0000-00-00 00:00:00', id], function(err, rows) {
					if (err)
						console.log(err);
				});
				// get user matched with him
				connection.query("SELECT id,lastname,firstname,picture,last_visit FROM `users` LEFT JOIN user_matchs ON user = ? AND mutual = '1' WHERE users.id = user_matchs.matched",
									[ id ], function (err, rows) {
					// create the chat or get it				
					async.each(rows, function(item, callback) {
						connection.query("SELECT * FROM chats WHERE (user_1 = ? AND user_2 = ?) OR (user_1 = ? AND user_2 = ?)", [ id, item.id, item.id, id ], function(err, rows) {
							// if no room exist for these users
							if (rows.length == 0) {
								// generate an id
								var uuid = 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function(c) {
									var r = Math.random()*16|0, v = c == 'x' ? r : (r&0x3|0x8);
									return v.toString(16);
								});
								// create the chat room
								connection.query("INSERT INTO chats (id, user_1, user_2) VALUES (?, ?, ?)", [ uuid, id, item.id ], function (error, rows) {
									item.id = uuid;
									callback();
								});
							} else {
								// else just use the id we got
								item.id = rows[0].id;
								callback();
							}
						});
					}, function(err) {
						// after that we can send the user list to the user
						socket.emit('user_list', rows);
					});
				});
				
				connection.release();
			});
		}
		// handle new message in a room
		socket.on('new_message', function(data) {
			if (id != undefined || data.chat == undefined || data.msg == undefined) {
				// get sql connection
				pool.getConnection(function (err, connection) {
					if ( err ) { return ; }
					
					// check that the chat exist
					connection.query("SELECT * FROM chats WHERE id = ? AND (user_1 = ? OR user_2 = ?)", [ data.chat, id, id], function(err, rows) {
						if (rows.length == 0) return ;
						// register the message
						connection.query('INSERT INTO chat_msgs (id, user, msg) VALUES (?, ?, ?)', [ data.chat, id, data.msg ], function (err, rows) {});	
						
						var other_guy;
						// get the id of the other guy
						if (id === rows[0].user_1)
							other_guy = rows[0].user_2;
						else if (id === rows[0].user_2)
							other_guy = rows[0].user_1;
						
						// if hes online send him the message
						if (users[other_guy] !== undefined) {
							users[other_guy].emit('new_message', {
								'from': data.chat,
								'msg': data.msg
							});
						}
						// if not just add the notification
						else {
							// generate an id
							var uuid = 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function(c) {
								var r = Math.random()*16|0, v = c == 'x' ? r : (r&0x3|0x8);
								return v.toString(16);
							});
							// query his name 
							connection.query('SELECT * FROM users WHERE id = ?', [ id ], function (err, rows) {
								if (rows.length > 0) {
									// build the message and insert it
									var msg = rows[0].firstname + " " + rows[0].lastname + " sent you a message when you were offline.";
									connection.query('INSERT INTO user_alerts (id, user, msg) VALUES (?, ?, ?)', [ uuid, other_guy, msg ], function (err2, rows2) {});
								}
							});	
						}
					});
					connection.release();
				});
			}
		})
		
		socket.on('alert_shown', function (data) {
			if (data.id != undefined && id != undefined) {
				// get sql connection
				pool.getConnection(function (err, connection) {
					if ( err ) { return ; }
					
					// set the alert as shown if he's the author and that the alert exist
					connection.query("SELECT * FROM user_alerts WHERE id = ?", [ data.id ],  function(err, rows) {
						if (rows.length > 0 && rows[0].user === id) {
							connection.query("UPDATE user_alerts SET shown = '1' WHERE id = ?", [ data.id ],  function(err, rows) {});
						}
					});
					// send to client
					
					connection.release();
				});
			}
		});
		
		socket.on('', function (data) {
			
		});
		
		socket.on('disconnect', function () {
			if (id != undefined) {
				// delete him from connected users
				delete users[id]; 
				
				// get sql connection
				pool.getConnection(function (err, connection) {
					if ( err ) { return ; }
					
					// set his last visit
					connection.query("UPDATE users SET last_visit = NOW() WHERE id = ?", [ id], 
						function(err, rows) {
							if (err)
								console.log(err);
					});
					// send to client
					
					connection.release();
				});
			}
		});
	});
}