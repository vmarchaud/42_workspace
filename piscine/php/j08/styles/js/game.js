
	function render_ship(item, index) {
		let start = 'case' + parseInt(item.position[1] * item.position[0]);
		$("#" + start).css("background", "url(" + position.sprite + ")");
		$("#" + start).attr("colspan", item.size[1]);
		$("#" + start).attr("rowspan", item.size[0]);
	}
	
	$.get("/api/map.php", function(data, status) {
		if (data) {
			let ships = JSON.parse(data);
			ships.forEach(render_ship);
		}
		else {
			alert("Cannot receive map information from server.")
		}
	});