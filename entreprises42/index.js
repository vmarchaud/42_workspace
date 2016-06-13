const	fs		= require('fs');
const	request = require('request');
const	cheerio = require('cheerio');

String.prototype.replaceAll = function(search, replacement) {
	var target = this;
	return target.replace(new RegExp(search, 'g'), replacement);
};

var id = process.argv[2];
if (id == undefined || process.argv.length < 3) {
	console.log("no id");
	return ;
}

var httpoptions = {
	url: 'https://entreprises.42.fr/offers/' + id,
	headers: {
		'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.63 Safari/537.36',
		'Cookie': '_entreprises_session=aW5IWVUxUWJRTzNHWGw5NkFQTm4xcWEyRzc5anNUcjAreWRkZmFuNjRpU0FxYjgzQ2VuUTJGQWdvZ1IwVDI3elRROFZ4ZHZJTWtKeTd3ZjN4NDVsUmtIa3hYRWJaRlo1bTBQVVZ5cGFabnhjRnlGekw1NGcremdGQ3VENzJmV002V3NZdVlraWVlM3BVZ3BGRUROeTZzTXJhSmxPVjJieFB6dUgxUTVEb1o3ODhoM3krU3dzTkdIbjF2THpTUW9xOUhwc3gwZktVcmQwV0gzS3BQdnlyT2grVzF3aUhFeGtJSUVFZjJSSnYxZz0tLXQwb3c1eHNRR2gvSkR1QXd1NFYxcGc9PQ%3D%3D--dee236a9b3795332518787c78832534909d7d664'
	}
};

request(httpoptions, function(error, response, body) {
	if (error) {
		console.log(error);
		return ;
	}
	var $ = cheerio.load(body);

	var datas = { url: "https://entreprises.42.fr/offers/" + id};

	$('.the_content').filter(function(){
		var data = $(this);
		datas.title = data.children().first().text().replaceAll("\n", '');

		var stuffs = data.children('.row-fluid').map(function (idx, elem) {
			var key = $(this).children().eq(0).text().replaceAll('\n', '').replaceAll(' ', '_').toLowerCase();
			var value = $(this).children().eq(1).text().replaceAll('\n', '');
			datas[key] = value;	
		});
		data.children('h2').first().remove()
		data.children('.row-fluid').remove();
		data.children('.underline').remove();
		var regex = /(<([^>]+)>)/ig
		datas.text  = data.text().replace(regex, "").replaceAll('\n', '').replaceAll('^M', '').replace(/(\r\n|\r)/gm, " ").replaceAll('  ', '\n');
})
httpoptions = { method: 'PUT', url: 'http://status.hardfight.fr:9200/entreprises42/offers/' + id, body: datas, json: true };
request(httpoptions, function (error, reponse, body) {
	console.log(body);		
});

});
