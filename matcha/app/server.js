const express       = require('express');
const flash         = require('connect-flash');
const app           = express();

app.set('view engine', 'jade');
app.set('views', './app/views');
app.use(express.static('./app/public'));

app.use(require('cookie-parser')());
app.use(require('body-parser').urlencoded({ extended: true }));
app.use(require('express-session')({ secret: 'leswag42', resave: false, saveUninitialized: false }));

// Include database connection
require('./config/connection.js');

// Include all Routes
require('./routes/routes.js')(app);

// Middleware

app.use(function (req, res, next) {
  console.log('Requested ' + req.baseUrl + " at " + Date.now());
  next();
});

// Start the server
const server = app.listen(3000, function () {
  const port = server.address().port;
  console.log('Listening at http://localhost:%s', port);
});

module.exports.getApp = app;
