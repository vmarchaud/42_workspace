/**
 * isAuthenticated
 *
 * @module      :: Policy
 * @description :: Simple policy to allow any authenticated user
 *                 Assumes that your login action in one of your controllers sets `req.session.authenticated = true;`
 * @docs        :: http://sailsjs.org/#!/documentation/concepts/Policies
 *
 */
module.exports = function(req, res, next) {
    if (req.session.user !== undefined) {
        if (req.session.user.default_language == undefined)
            req.session.user.default_language = "en"
        req.setLocale(req.session.user.default_language);
        return next();
    }
    else{
        return res.redirect('/auth/login');
    }
};