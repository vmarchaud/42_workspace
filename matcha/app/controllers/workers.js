var schedule 	= require('node-schedule');
var events		= require('../config/event');
var async 		= require('async');
var pool 		= require('../config/connection.js');

// job used to calculate the public score of an user 
schedule.scheduleJob('*/10 * * * *', function() {
	var start = Date.now();
	
	pool.getConnection(function ( err, connection ) {
		if ( err ) return ;
		
		console.log("Computing public score of all users ...");
		
		var total_matchs, total_visits, total_users;
		// get nbr of visits
		connection.query("SELECT COUNT(*) AS count FROM visits WHERE 1", [], function (err, rows) {
			total_visits = rows[0].count;
		});
		// get nbr of matchs
		connection.query("SELECT (COUNT(*) /2) AS count FROM user_matchs WHERE `mutual` = 1 UNION SELECT COUNT(*) FROM user_matchs WHERE `mutual` = 0 ", [], function (err, rows) {
			total_matchs = rows[0].count + rows[1].count;
		});		
		
		// get all users
		connection.query("SELECT * FROM users WHERE 1", function (err, rows) {
			
			total_users = rows.length;
			// for each user calculate the score following the formula
			// (nbrVisit / visit_total) * nbrUsers + (nbrMatch / matchTotal) * nbrUsers - (nbrBlockedUsers * (100 / nbrUsers))
			async.each(rows, function (user, callback) {
				connection.query("SELECT COUNT(*) AS count FROM visits WHERE visited = ? UNION ALL SELECT COUNT(*) FROM user_matchs WHERE matched = ? UNION ALL SELECT COUNT(*) FROM user_blockeds WHERE blocked = ?",
						[user.id, user.id, user.id], function ( err, rows) {
					//compute score for the user
					var result = ( rows[0].count / total_visits) * total_users + (rows[1].count / total_matchs) * total_users - (rows[2].count * (100 / total_users));
					console.log("computed value for " + user.id + " : " + result);
					
					// put limit
					if (result < 0)
						result = 0;
					else if (result > 100)
						result = 100;
						
					// set it in db
					connection.query("UPDATE users SET score = ? WHERE id = ?", [ result, user.id ], function (err, rows) {
						callback();
					});
				})
			}, function ( err) {
				console.log("Computing finished in " + (Date.now() - start) + " ms");
			});
		});
		// release connection
		connection.release();
	});
});