/**
 * User.js
 *
 * @description :: TODO: You might write a short summary of how this model works and what it represents here.
 * @docs        :: http://sailsjs.org/documentation/concepts/models-and-orm/models
 */

var bcrypt = require('bcryptjs');

module.exports = {

  attributes: {
      email: {
          type: 'email',
          required: true,
          unique: true,
          email: true
      },
      pwd: {
          type: 'string'
      },
      firstname: {
          type: 'string',
          minLength: 3,
          required: true
      },
      lastname: {
          type: 'string',
          minLength: 3,
          required: true
      },
      default_language:{
          type: 'string',
          defaultsTo: 'en'
      },
      image : {
          type: 'url'
      },
      movies: {
        type: 'array',
        defaultsTo: []
      }
  },

  beforeCreate: function(user, cb) {
	// if he log via facebook, dont hash the password
	if (user.pwd == undefined || user.pwd.length == 0){
        cb();
    }

	// if its local strategy, hash it
	else {
        bcrypt.genSalt(10, function(err, salt) {
			bcrypt.hash(user.pwd, salt, function(err, hash) {
				if (err) {
					sails.log.debug("Cant hash a password");
					cb(err);
				} else {
					user.pwd = hash;
					cb();
				}
			});
		});
	}
  }
};
