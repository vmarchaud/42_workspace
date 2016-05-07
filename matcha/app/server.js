const express       = require('express');
const passport      = require('passport');
const LocalStrategy = require('passport-local').Strategy;
const flash         = require('connect-flash');
const app           = express();

app.set('view engine', 'jade');
app.set('views', './app/views');
app.use(express.static('./app/public'));
app.use(require('cookie-parser')());
app.use(require('body-parser').urlencoded({ extended: true }));
app.use(require('express-session')({ secret: 'leswag42', resave: false, saveUninitialized: false }));

app.use(flash());

// Include all Routes
require('./config/routes/routes')(app);

// Start the server
const server = app.listen(3000, function () {
  const port = server.address().port;
  console.log('Listening at http://localhost:%s', port);
});

module.exports.getApp = app;
