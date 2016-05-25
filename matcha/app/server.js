var express      	= require('express');
var session 		= require('express-session');
var sharedsession 	= require("express-socket.io-session");
var morgan 			= require('morgan');
var compression 	= require('compression');
var async		 	= require('async');
var app         	= express();
var server 			= require('http').Server(app);
var io 				= require('socket.io')(server);
var events		 	= require('./config/event');

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


// socket list
var users = {};

// require socket io server
io.use(sharedsession(session_setup));
require('./controllers/socket')(io, users);

// require event
require('./controllers/events')(users);

// Start the server
server.listen(3000);

console.log("Listening connection on port 3000");


module.exports = events;
