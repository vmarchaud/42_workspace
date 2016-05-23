var express      	= require('express');
var session 		= require('express-session');
var sharedsession 	= require("express-socket.io-session");
var morgan 			= require('morgan');
var compression 	= require('compression');
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
			connection.query("UPDATE users SET last_visit=? WHERE id = ?", [ '0000-00-00 00:00:00', id], 
				function(err, rows) {
					if (err)
						console.log(err);
				});
			// get user matched with him
			connection.query("SELECT id,lastname,firstname,picture,last_visit FROM `users` LEFT JOIN user_matchs ON user = ? AND mutual = '1' WHERE users.id = user_matchs.matched",
								[ id ], function (err, rows) {
									socket.emit('user_list', rows);
								});
			
			connection.release();
		});
	}
	
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
