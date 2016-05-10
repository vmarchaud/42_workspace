module.exports = function(app, pool) {
  /**
   * Display Home Page
  **/
  app.get('/', function(req, res) {
    res.render('index', {
      title: 'Your page title',
      message: 'Your header message',
      userName: (req.user) ? req.user.username : undefined
    });
  });
}
