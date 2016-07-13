/**
 * Movie.js
 *
 * @description :: TODO: You might write a short summary of how this model works and what it represents here.
 * @docs        :: http://sailsjs.org/documentation/concepts/models-and-orm/models
 */

module.exports = {

  attributes: {
    imdb_id: {
      required: true,
      type: 'string',
      unique: false
    },
    release_date: {
      type: 'date'
    },
    synopsis: {
      type: 'text'
    },
    poster_url: {
      type: 'string',
      defaultsTo: 'http://image.tmdb.org/t/p/w1280//oQWWth5AOtbWG9o8SCAviGcADed.jpg'
    },
    backdrop_url: {
      type: 'string',
      defaultsTo: 'http://image.tmdb.org/t/p/w1280//XvJCJ5LBHTWQxsQN9Sddphp7xe.jpg'
    },
    title: {
      type: 'string'
    },
    vote_average: {
      type: 'float'
    },
    popularity: {
      type: 'float'
    },
    cast: {
      type: 'json',
      defaultsTo: null
    },
  	torrent: {
  	  model: 'torrent'
  	}
  }
};
