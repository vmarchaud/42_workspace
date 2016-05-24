var express      	= require('express');
var session 		= require('express-session');
var sharedsession 	= require("express-socket.io-session");
var morgan 			= require('morgan');
var compression 	= require('compression');
var async		 	= require('async');
var app         	= express();
var server 			= require('http').Server(app);
var io 				= require('socket.io')(server);

// Include all routes
var index 	= require('./controllers/index');
var auth 	= require('./controllers/auth');
var account = require('./controllers/account');
var search 	= require('./controllers/search');
var profile = require('./controllers/profile');
var user 	= require('./controllers/user');
var pool 	= require('./config/connection.js');

// Setup view engine
app.set('view engine', 'jade');
app.set('views', './app/views');

// Setup static file folder
app.use(express.static('./app/public'));

// Setup the logger
app.use(morgan('dev'));

// Setup the compression engine
app.use(compression());

// Setup the body parser that will parse the form sent by client
app.use(require('body-parser').urlencoded({ extended: true }));

// Setup session
var session_setup = session({
  secret: 'keyboard cat',
  resave: false,
  saveUninitialized: true
});

app.use(session_setup);

// Register routes
app.use('/', index);
app.use('/profile', function(req, res, next) {
	if (req.session.user == undefined) 
		res.redirect("/#login");
	else
		next();
}, profile);
app.use('/auth', auth);
app.use('/me', function(req, res, next) {
	if (req.session.user == undefined) 
		res.redirect("/#login");
	else
		next();
}, account);

app.use('/search', function(req, res, next) {
	if (req.session.user == undefined) 
		res.redirect("/#login");
	else
		next();
}, search);

app.use('/user', function(req, res, next) {
	if (req.session.user == undefined) 
		res.redirect("/#login");
	else
		next();
}, user);

io.use(sharedsession(session_setup));

// socket list
var users = {};

// register websocket 
io.on('connection', function (socket) {
	
	var id = socket.handshake.session.user;
	// if the user is connected
	if (id != undefined) {
		
		// store the user socket
		users[id] = socket;
		socket.emit('handshake', { 'id': id });
		
		// get sql connection
		pool.getConnection(function (err, connection) {
			if ( err ) { return ; }
			
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
		console.log('new_message received : ' + data.msg);
		if (id != undefined || data.chat == undefined || data.msg == undefined) {
			// get sql connection
			pool.getConnection(function (err, connection) {
				if ( err ) { return ; }
				
				// check that the chat exist
				connection.query("SELECT * FROM chats WHERE id = ? AND (user_1 = ? OR user_2 = ?)", [ data.chat, id, id], function(err, rows) {
					if (rows.length == 0) return ;
					// register the message
					connection.query('INSERT INTO chat_msgs (id, user, msg) VALUES (?, ?, ?)', [ data.chat, id, data.msg ], function (err, rows) {});	
					// send it to the other user if hes online
					if (id === rows[0].user_1 && users[rows[0].user_2] !== undefined) {
						users[rows[0].user_2].emit('new_message', {
							'from': data.chat,
							'msg': data.msg
						});
					} else if (id === rows[0].user_2 && users[rows[0].user_1] !== undefined){
						users[rows[0].user_1].emit('new_message', {
							'from': data.chat,
							'msg': data.msg
						});
					}
				});
				 
				
				connection.release();
			});
		}
	})
	
  	socket.on('disconnect', function () {
    	if (id != undefined) {
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


// Start the server
server.listen(3000);


module.exports = app;
