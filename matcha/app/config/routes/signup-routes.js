const passport = require('passport');

module.exports = function(app) {
  /**
   * Receive Signin Form Data
  **/
  app.post('/signin',
    passport.authenticate('local-login', { failureRedirect: '/' }),
    function(req, res) {
      res.redirect('/');
  });

  /**
   * Display Signup Form
  **/
  app.get('/signup', function(req, res) {
    res.render('signup', {
      title: 'Your title',
      message: 'Your Message',
      userName: (req.user) ? req.user.username : undefined,
      flashMessage: req.flash('flashMessage')
    });
  });

  /**
   * Receive Signup Form Data
  **/
  app.post('/signup', function(req, res) {
    
      connection.query("SELECT * FROM users WHERE username = ?", [username],
      function(err, rows) {
        if (err) {
          return done(err);
        }

        if (rows.length) {
          return done(null, false, req.flash('flashMessage', 'Sorry! That username is already taken.'));
        } else {
          const User = {
            username: username,
            email: req.body.email,
            password: bcrypt.hashSync(password, salt)
          };

          const insertQuery = "INSERT INTO users (username, email, password) values (?,?,?)";

          connection.query(insertQuery, [User.username, User.email, User.password],
            function(err, rows) {
              if (err) {
                console.log(err);
                return done(null, false, req.flash('flashMessage', 'Sorry! That email is already taken.'));
              }

              User.id = rows.insertId;

              return done(null, User);
          });
        }
      })
      res.redirect('/');
  });
}
