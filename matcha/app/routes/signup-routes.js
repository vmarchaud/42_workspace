var pool = require('../config/connection.js');

module.exports = function(app) {
  /**
   * Receive Signin Form Data
  **/
  app.post('/signin', function(req, res) {
      res.sendStatus(401);
  });

  /**
   * Display Signup Form
  **/
  app.get('/signup', function(req, res) {
    console.log('signup');
    res.render('signup', {
      title: 'Your title',
      message: 'Your Message',
      userName: (req.user) ? req.user.username : undefined
    });
  });

  // Signup form
  app.post('/signup', function(req, res) {
      
      pool.getConnection(function(err, connection) {
        connection.query("SELECT * FROM users WHERE username = ?", [username],  function(err, rows) {
          if (err) {
            connection.release(); 
            return done(err);
          }

          if (rows.length) {
            connection.release();
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
      });

      
      res.redirect('/');
  });
}
