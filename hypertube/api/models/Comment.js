/**
 * Comment.js
 *
 * @description :: TODO: You might write a short summary of how this model works and what it represents here.
 * @docs        :: http://sailsjs.org/documentation/concepts/models-and-orm/models
 */

module.exports = {

  attributes: {
    comment:{
      type: 'string',
      required: true
    },
    movie_id:{
      type: 'string',
      required: true
    },
    user:{
      model: 'user',
      required: true
    }
  }
};

