/**
 * Subtitle.js
 *
 * @description :: TODO: You might write a short summary of how this model works and what it represents here.
 * @docs        :: http://sailsjs.org/documentation/concepts/models-and-orm/models
 */

module.exports = {

  attributes: {
      // the language of the subtitle
      lang: {
          type: 'string'
      },
      // The path of subtitle file
      path: {
          type: 'string'
      },
      // the torrent of the subtitle
      torrent: {
          model: 'torrent'
      }
  }
};

