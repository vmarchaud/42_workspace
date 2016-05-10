var express      	= require('express');
var session			= require('express-session');
var utils			= require('./config/utils');
var morgan 			= require('morgan');
var compression 	= require('compression');
var app         	= express();

// Include all routes
var index = require('./routes/index');
var auths = require('./routes/auth');

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
  resave: false,
  saveUninitialized: true,
  secret: 'keyboard cat',
  cookie: { maxAge: 60000 }
}));

// Register routes
app.use('/', index);
app.use('/', auths);

// Start the server
const server = app.listen(3000, function () {
  const port = server.address().port;
  console.log('Listening at http://localhost:%s', port);
});

module.exports = app;
