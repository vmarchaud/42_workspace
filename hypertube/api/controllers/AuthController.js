/**
 * AuthController
 *
 * @description :: Server-side logic for managing auths
 * @help        :: See http://sailsjs.org/#!/documentation/concepts/Controllers
 */

var passport = require('passport');

module.exports = {

    login: function(req, res) {
        passport.authenticate('local', function(err, user, info) {
            if ((err) || (!user)) {
                req.session.msg = 'Mmmmh, login has failed.';
                return res.redirect('/auth/login')
            }
            req.logIn(user, function(err) {
                if (err) res.send(err);
                req.session.user = user;
                res.redirect('/');
            });
        })(req, res);
    },

	facebook: function(req, res) {
        passport.authenticate('facebook', { successRedirect: '/', failureRedirect: '/auth/login', scope: ['public_profile','email', 'picture']}, function(err, user, info) {
            if (err || !user) {
				// handle error 
                return res.send({
                    err: err,
                    info: info,
                    user: user
                });
            }

			// login via passport
            req.logIn(user, function(err) {
                if (err)
                    return res.send(err);
				req.session.user = user;
                return res.redirect('/');
            });
        })(req, res);
    },

    duoquadra: function(req, res) {
        passport.authenticate('oauth2', { successRedirect: '/', failureRedirect: '/auth/login', scope: ['public_profile','email', 'picture']}, function(err, user, info) {
            if (err || !user) {
				// handle error 
                return res.send({
                    err: err,
                    info: info,
                    user: user
                });
            }

			// login via passport
            req.logIn(user, function(err) {
                if (err)
                    return res.send(err);
				req.session.user = user;
                return res.redirect('/');
            });
        })(req, res);
    },

    logout: function(req, res) {
		// be sure about destroying a session
        req.session.destroy(function(err) {
           return res.redirect('/');
      	});
    }
};

