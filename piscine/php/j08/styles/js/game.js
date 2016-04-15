
	function render_ship(item, index) {
		console.log(item);
		var start = parseInt(item.position[0] + item.position[1] * 100);
		for (var x = 0; x < item.size[0]; x++) {
			var eval = parseInt(start + x);
			eval = "#case" + eval;
			$(eval).css("background-color", "red");
		}
		for (var y = 1; y < item.size[1]; y++) {
			var eval = parseInt(start + y * 100);
			eval = "#case" + eval;
			$(eval).css("background-color", "red");
		}
	}


	$.get("/api/map.php", function(data, status) {
		if (data) {
			data.forEach(render_ship);
		}
		else {
			alert("Cannot receive map information from server.")
		}
	});
