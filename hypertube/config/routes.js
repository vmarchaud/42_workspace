/**
 * Route Mappings
 * (sails.config.routes)
 *
 * Your routes map URLs to views and controllers.
 *
 * If Sails receives a URL that doesn't match any of the routes below,
 * it will check for matching files (images, scripts, stylesheets, etc.)
 * in your assets directory.  e.g. `http://localhost:1337/images/foo.jpg`
 * might match an image file: `/assets/images/foo.jpg`
 *
 * Finally, if those don't match either, the default 404 handler is triggered.
 * See `api/responses/notFound.js` to adjust your app's 404 logic.
 *
 * Note: Sails doesn't ACTUALLY serve stuff from `assets`-- the default Gruntfile in Sails copies
 * flat files from `assets` to `.tmp/public`.  This allows you to do things like compile LESS or
 * CoffeeScript for the front-end.
 *
 * For more information on configuring custom routes, check out:
 * http://sailsjs.org/#!/documentation/concepts/Routes/RouteTargetSyntax.html
 */

var passport = require('passport');

module.exports.routes = {

  /***************************************************************************
  *                                                                          *
  * Make the view located at `views/homepage.ejs` (or `views/homepage.jade`, *
  * etc. depending on your default view engine) your home page.              *
  *                                                                          *
  * (Alternatively, remove this and add an `index.html` file in your         *
  * `assets` directory)                                                      *
  *                                                                          *
  ***************************************************************************/

  '/error': {
    view: 'error'
  },

  // Movie Controller
  'get /': 'MovieController.search',
  'get /movie/search': 'MovieController.search',
  'get /movie/partial/:id': 'MovieController.partial',
  'get /movie/search/:name': 'MovieController.search',
  'get /movie/play/:id': 'MovieController.play',
  'post /movie/add_comment/:id': 'MovieController.add_comment',

  // Search a torrent
  'get /torrent/search/:name': 'TorrentController.search',

  // Download a torrent
  'get /torrent/:id/download': 'TorrentController.download',

  // Stream a torrent
  'get /torrent/:id/stream': 'TorrentController.stream',

  // Search a subtitle for this torrent
  'get /torrent/:id/subtitle/:lang': 'SubtitleController.search',

  'get /auth/login': {
    view: 'user/connexion'
  },

  'post /auth/login': 'AuthController.login',

  // Cette route là va rediriger l'utilisateur sur facebook
  '/auth/facebook': passport.authenticate('facebook', { scope: ['public_profile', 'email'] }),

  // Cette route là va rediriger l'utilisateur sur l'intra de 42
  '/auth/duoquadra': passport.authenticate('oauth2'),

  // Celle-ci va être call après facebook
  '/auth/facebook/callback': 'AuthController.facebook',

  // Celle ci va etre call apres l'api de l'intra
  '/auth/duoquadra/callback': 'AuthController.duoquadra',

  '/auth/logout': 'AuthController.logout',

  'get /auth/signup': {
    view: 'user/register'
  },

  '/my_profil': 'UserController.my_profil',

  '/lost_password': {
    view: 'user/lost_password'
  },

  '/send_reset_pwd': 'UserController.send_reset_pwd',

  '/new_pwd': 'UserController.new_pwd',

  'get /reset_pwd': 'UserController.reset_pwd',

  '/update_picture' : 'UserController.edit_picture',

  '/update_info' : 'Usercontroller.edit_info',

  'get /user/:id' : 'UserController.findOne',

  'post /user' : 'UserController.create',

/***************************************************************************
  *                                                                          *
  * Custom routes here...                                                    *
  *                                                                          *
  * If a request to a URL doesn't match any of the custom routes above, it   *
  * is matched against Sails route blueprints. See `config/blueprints.js`    *
  * for configuration options and examples.                                  *
  *                                                                          *
  ***************************************************************************/
};
