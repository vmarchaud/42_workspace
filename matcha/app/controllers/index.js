var express = require('express');
var router = express.Router();

  /**
   * Display Home Page
  **/
  router.get('/', function(req, res) {
	console.log(req.session.user);
	res.render('index', {
	  title: 'Your page title',
	  message: 'Your header message',
	  connected: req.session.user !== undefined,
	  userName: (req.user) ? req.user.username : undefined
	});
  });


module.exports = router;