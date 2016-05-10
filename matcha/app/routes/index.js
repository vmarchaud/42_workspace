var express = require('express');
var router = express.Router();

  /**
   * Display Home Page
  **/
  router.get('/', function(req, res) {
	res.render('index', {
	  title: 'Your page title',
	  message: 'Your header message',
	  userName: (req.user) ? req.user.username : undefined
	});
  });


module.exports = router;