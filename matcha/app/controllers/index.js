var express = require('express');
var router = express.Router();

  /**
   * Display Home Page
  **/
  router.get('/', function(req, res) {
	if (req.session.user !== undefined) {
		res.render('home', {
			title: 'Home | Matcha',
			connected: req.session.user !== undefined
		});
	} else {
		res.render('index', {
			title: 'Index | Matcha',
			message: 'Your header message',
			connected: req.session.user !== undefined,
			userName: (req.user) ? req.user.username : undefined
		});
	}
	
  });


module.exports = router;