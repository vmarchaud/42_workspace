/**
 * Torrent.js
 *
 * @description :: This model represente a torrent that has been crawled, he may not be fully downloaded
 * @docs        :: http://sailsjs.org/documentation/concepts/models-and-orm/models
 */

module.exports = {
  attributes: {
    // the title of the torrent
	title:  {
		type: 'string'
	},
    // size of the torrent
    size : {
        type: 'string'
    },
    // kickass or piratebay
	source : {
		type: 'string'
	},
    // nbr of seeders
	seeds : {
        type: 'string'
    },
    // magnet url
    magnet : {
        type: 'text'
    },
    // any additional information on the torrent
    info : {
        type: 'json'
    },
    // if the video has been downloaded
    download : {
        type: 'boolean'
    },
    // the path to the video file
    path : {
        type: 'text'
    },
	mime : {
		type: 'string'
	},
    // all of the subtitles that are linked to this torrent
    subtitles : {
      collection: 'subtitle',
      via: 'torrent'
    }
  }
};

