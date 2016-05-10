var pool = require('../config/connection.js');
var bcrypt = require('bcryptjs');
var salt = "leswagdu42";
var express = require('express');
var router = express.Router();

  /**
   * Receive Signin Form Data
  **/
  router.post('/signin', function(req, res) {
	 var mail = req.body.mail, pwd = req.body.pwd;
	 
	 // is requested correctly formed
	 if (mail == undefined || pwd == undefined) {
	 	res.sendStatus(500);
	 	return ;
	 }
	 // get connection from the pool
	 pool.getConnection(function(err, connection) {
	   if (err) {
		  res.sendStatus(500); return ;
	   }
	   // Make the request to verify that the data are good
	   connection.query("SELECT * FROM users WHERE mail = ? AND password = ?", [mail, bcrypt.hashSync(pwd, salt)],  function(err, rows) {
		  // If not found return a 404
		  if (err)
			res.sendStatus(404);
		  // Else send a success and save it in session
		  else {
		  	res.sendStatus(200);
			  
		  }
		})
	  });
  });

  /**
   * Display Signup Form
  **/
  router.get('/signup', function(req, res) {
	res.render('signup', {
	  title: 'Your title',
	  message: 'Your Message',
	  userName: (req.user) ? req.user.username : undefined
	});
  });

module.exports = router;