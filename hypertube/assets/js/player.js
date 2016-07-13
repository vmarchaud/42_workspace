var torrentID = null;
var player = videojs("player");

// Show modal

$('#waitModal').modal({
    backdrop: 'static'
})
var waitModalText = $("#waitModalText");

// Pseudo loading
var loading = setInterval(function() {
	var tmp = $("#waitModalText").children()[0].innerHTML;
	if (tmp.indexOf('...') > 0) 
		$("#waitModalText").children()[0].innerHTML = _.replace(tmp, '...', '');
	 else 
		$("#waitModalText").children()[0].innerHTML += '.';
}, 500);

// Start searching torrent

waitModalText.append("<p>> Searching for a torrent </p>");

$.get("/torrent/search/" + $("#title").text()).done(function (data) {

	waitModalText.append("<p>> Found a torrent available, starting download </p>");
	
	// query for user subtitle
	$.get("/torrent/" + data.id + "/subtitle/mine").done(function (subtitle) {
		if (subtitle.lang !== "en") {
			player.addRemoteTextTrack({
				kind: "captions",
				lang: subtitle.lang,
				label: subtitle.lang,
				src: "/videos/" + data.id + "/" + subtitle.lang + ".vtt"
			})
		}
	});
	
	// start the download
	$.get("/torrent/" + data.id + "/download").done(function (torrent) {
			waitModalText.append("<p>> Ready ! </p>");
			// stop the loading task
			clearInterval(loading);
			// clear modal
			$('#waitModal').modal('hide');
			
			// setup the player
			player.pause();
			player.src([
				{ type: torrent.mime, src: "/torrent/" + data.id + "/stream" }
			]);
			player.addRemoteTextTrack({
				kind: "captions",
				lang: "en",
				label: "en",
				src: "/videos/" + data.id + "/en.vtt"
			})
     		$("#div_video").removeClass("vjs-playing").addClass("vjs-paused");
			player.load();
			// and play
		
	}).fail(function (err) {
		console.log(err)
		waitModalText.append("<p>! Cant start the torrent download for unknown reason </p>");
	});
}).fail(function (err) {
	waitModalText.append("<p>! No torrent available or our provider are down, sorry </p>");
});
