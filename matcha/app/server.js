var express      	= require('express');
var session 		= require('express-session')
var morgan 			= require('morgan');
var compression 	= require('compression');
var app         	= express();

// Include all routes
var index = require('./controllers/index');
var auth = require('./controllers/auth');
var account = require('./controllers/account');
var search = require('./controllers/search');

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
app.use(session({
  secret: 'keyboard cat',
  resave: false,
  saveUninitialized: true
}));

// Register routes
app.use('/', index);
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

// Start the server
const server = app.listen(3000, function () {
  const port = server.address().port;
  console.log('Listening at http://localhost:%s', port);
});

module.exports = app;
