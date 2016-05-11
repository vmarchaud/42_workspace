var pool 	= require('../config/connection.js');
var bcrypt 	= require('bcryptjs');
var salt 	= bcrypt.genSaltSync(10);;
var express = require('express');
var router 	= express.Router();

  /**
   * Receive Signin Form Data
  **/
  router.post('/signin', function(req, res) {
	 var mail = req.body.mail, pwd = req.body.pwd;
	 
	 // is requested correctly formed
	 if (mail == undefined || pwd == undefined) {
	 	res.sendStatus(400); return ;
	 }
	 // get connection from the pool
	 pool.getConnection(function(err, connection) {
	   if (err) {
		  res.sendStatus(500); return ;
	   }
	   // Make the request to verify that the data are good
	   connection.query("SELECT * FROM users WHERE mail = ? AND password = ?", [mail, bcrypt.hashSync(pwd, salt)],  function(err, rows) {
		  // If not found return a 404
		  if (err || rows.length == 0)
			res.sendStatus(404);
		  // Else send a success and save it in session
		  else {
		  	res.sendStatus(200);
			req.session.user = rows[0].id;
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
	  connected: req.session.user !== undefined,
	  userName: (req.user) ? req.user.username : undefined
	});
  });
  
  /**
   * Receive Signup Form Data
  **/
  router.post('/signup', function(req, res) {
	 var mail = req.body.mail, pwd = req.body.pwd, firstname = req.body.firstname, lastname = req.body.lastname;
	 
	 // is request correctly formed
	 if (mail == undefined || pwd == undefined || firstname == undefined || lastname == undefined) {
	 	res.sendStatus(400); return ;
	 }
	 // get connection from the pool
	 pool.getConnection(function(err, connection) {
	   if (err) {
		  res.sendStatus(500); return ;
	   }
	   // Make the request to verify that the mail already exist or not
	   connection.query("SELECT * FROM users WHERE mail = ?", 
	   		[mail],  function(err, rows) {
		  // If found return a conflict
		  if (err || rows.length > 0)
			res.sendStatus(409);
		  // Else create the account
		  else {
			// Generate an uuid
			var uuid = 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function(c) {
				var r = Math.random()*16|0, v = c == 'x' ? r : (r&0x3|0x8);
				return v.toString(16);
			});
			// make the request
			connection.query("INSERT INTO users (id, mail, password, firstname, name, state) VALUES (?, ?, ?, ?, ?, ?)", 
				[uuid, mail, bcrypt.hashSync(pwd, salt), firstname, lastname, 'NOT_ACTIVATED'], function (err, rows) {
					// maybe ?
					if (err) {
						res.sendStatus(500);
						return ;
					}
				});
			// Else its good
		  	res.sendStatus(200);
			res.session.user = uuid;
			console.log(res.session.user);
		  }
		})
	  });
  });

module.exports = router;