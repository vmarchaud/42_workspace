/**
 * Scheduler
 *
 * @description :: Scheduler for background task
 */

const fs		= require("fs-extra");
const async 	= require("async");

module.exports.crontabs = [
      {
         interval : '10 * * * *',
         task : function () {
			// get date that if movie is inferior, remove them
			var nowMinus30Days = new Date(Date.now() - (30 * 24 * 60 * 60 * 1000));

            Torrent.find().where({ updatedAt : {
				"<" : nowMinus30Days
			}}).exec(function ( err, results ) {
				if (err || results.length == 0)
					return ;
				// for each old torrent, delete the file
				async.forEach(results, function ( item, callback) {
					sails.log.debug("Jobs | Deleting torrent " + item.id + " cause hes 30 days old");
					// reset value
					item.download = false;
					item.mime = null;
					// delete file
					fs.unlinkSync(process.cwd() + "/.tmp/private" + item.path);
					item.path = null;
					// register in the db
					item.save();
					callback();
				},
				function ( err ) {
					sails.log.debug("Jobs | Deleted " + results.length + " torrent that too old");
				})
			});
        }
	}
];