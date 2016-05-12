var express = require('express');
var router = express.Router();

  /**
   * Display Home Page
  **/
  router.get('/', function(req, res) {
	res.render('index', {
	  title: 'Home | Matcha',
	  message: 'Your header message',
	  connected: req.session.user !== undefined,
	  userName: (req.user) ? req.user.username : undefined
	});
  });


module.exports = router;