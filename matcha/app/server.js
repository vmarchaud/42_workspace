var express      	= require('express');
var session 		= require('express-session');
var sharedsession 	= require("express-socket.io-session");
var morgan 			= require('morgan');
var compression 	= require('compression');
var app         	= express();
var server 			= require('http').Server(app);
var io 				= require('socket.io')(server);

// Include all routes
var index = require('./controllers/index');
var auth = require('./controllers/auth');
var account = require('./controllers/account');
var search = require('./controllers/search');
var profile = require('./controllers/profile');
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
app.use('/profile', profile);
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

io.use(sharedsession(session_setup));

// register websocket keep alive
io.on('connection', function (socket) {

	// if the user is connected
	if (socket.handshake.session.user != undefined) {
		// get sql connection
		pool.getConnection(function (err, connection) {
			if ( err ) { return ; }
			
			connection.query("UPDATE users SET last_visit=? WHERE id = ?", [ '0000-00-00 00:00:00', socket.handshake.session.user], 
				function(err, rows) {
					if (err)
						console.log(err);
				});
			connection.release();
		});
	}
	
	
  	socket.on('disconnect', function () {
		console.log(socket.handshake.session.user + " disconnected");
    	if (socket.handshake.session.user != undefined) {
			// get sql connection
			pool.getConnection(function (err, connection) {
				if ( err ) { return ; }
				
				connection.query("UPDATE users SET last_visit=? WHERE id = ?", [ 'NOW()', socket.handshake.session.user], 
					function(err, rows) {
						if (err)
							console.log(err);
				});
				
				connection.release();
			});
		}
  	});
});


// Start the server
server.listen(3000);


module.exports = app;
