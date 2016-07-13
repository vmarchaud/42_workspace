/**
 * SubtitleController
 *
 * @description :: Server-side logic for managing Subtitles
 * @help        :: See http://sailsjs.org/#!/documentation/concepts/Controllers
 */

module.exports = {
    /**
    *   `SubtitleController.search()`
    *   /torrent/:id/subtitle/:lang
    *
    *   Route used to search a subtitle for a specific torrent
    */
    search: function (req, res) {
        var id = req.params.id, lang = req.params.lang;

        if (lang == "mine")
            lang = req.session.user.default_language;

        Torrent.find({ id: id }).populate('subtitles', { lang: lang }).exec(function (err, records) {
            // check if we found a torrent for this id
            if ( err || records.length == 0) {
                res.json({ error: "Torrent not found" });
            } else {
                var torrent = records[0];

                // if there is no subtitles, we can already search it
                if (torrent.subtitles.length == 0) {
                    var subtitle = SubtitleService.search(torrent, lang, function ( err, results) {
                        if (err)
                            res.json(err);
                        else 
                            res.json(results);
                    });
                } 
                // else just return our subtitle
                else
                    res.ok(torrent.subtitles[0]);
            }
        });
    }
};

