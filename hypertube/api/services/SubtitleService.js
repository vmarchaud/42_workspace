/**
 * SubtitleService
 *
 * @description :: Server-side service to search and download subtitles
 * @help        :: See http://sailsjs.org/#!/documentation/concepts/Controllers
 */

const fs            = require("fs-extra");
const OS            = require('opensubtitles-api');
const srt2vtt       = require('srt-to-vtt')
const OpenSubtitles = new OS('OSTestUserAgent');
const request       = require('request');

module.exports = {

    /**
    * `SubtitleService.search()`
    *
    *   Function used to call a research on opensubtitles to find a subtitle
    */
    search: function ( torrent, lang , callback) {
        // Start the research
        OpenSubtitles.search({
            sublanguageid: lang,
            filesize: torrent.size,
            extensions: ['srt', 'vtt'], 
            limit: 'best',
            query: torrent.title + " " + torrent.info.year
        }).then(function ( subtitles ) {
            // if we found a subtitle for this lang
            if (subtitles[lang] !== undefined) {

                var path = process.cwd() + '/.tmp/public/videos/' + torrent.id + '/';

                fs.mkdirs(path, function ( err ) {
                    if (err)
                        callback({ error: "Cant write subtitles on the disk.", log: err });
                    else {
                        // convert the subtitle
                         request(subtitles[lang].url)
                        .pipe(srt2vtt())
                        .pipe(fs.createWriteStream(path + "/" + lang + ".vtt"));

                        // register it into the db
                        Subtitle.create({ lang: lang, path: '/videos/' + torrent.id + "/" + lang + ".vtt", torrent: torrent }, function (err, model) {
                            if ( err )
                                callback({ error: "Cant save the subtitle into the database.", log: err });
                            else {
                                sails.log.debug("SubtitleService |  Subtitle in " + lang + " as been found and registered for torrent" + torrent.id);
						        callback(undefined, model.toJSON());
                            }
                        });
                    }
                })
            }
        }).catch(function ( err ) {
            callback({ error: "Error while trying to search for subtitles.", log: err});
        });
    }
};

