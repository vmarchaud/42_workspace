window.onload = function() {

	function getCookie(name) {
		var dc = document.cookie.split(";");
		for(var i = 0; i < dc.length; i++) {
			var value = dc[i].split("=");
			if (value[0] === name)
				return value[1];
		}
		return null;
	}

	function saveCookie(name) {
		var todos = document.getElementById("ft_list");
		var values = [];
		for(var i = 0; i < todos.childNodes.length; i++) {
			values.push(todos.childNodes[i].innerHTML);
		}
		console.log(values);
		var value = values.join("%%%");
		document.cookie = name + "=" + value + ";expires=Thu, 18 Dec 2017 12:00:00 UTC";
	}

	var cookie = getCookie("ft_list");
	if (cookie != null) {
		var todos = document.getElementById("ft_list");
		var tab = cookie.split("%%%");
		for(var i = 0; i < tab.length; i++) {
			var todo = document.createElement("div");
			todo.innerHTML = tab[i];
			todo.addEventListener("click", function(obj) {
				var valid = confirm("Sure ?");
				if (valid) {
					todos.removeChild(obj.target);
					saveCookie("ft_list");
				}
			});
			todos.appendChild(todo);
		}
	}



	var add = document.getElementById("new");
	add.addEventListener("click", function() {
		var input = prompt("Please input the name of todo", "");
		if (input.length == 0)
		return ;
	var todo = document.createElement('div');
	todo.innerHTML = input;
	var todos = document.getElementById("ft_list");
	todo.addEventListener("click", function(obj) {
		var valid = confirm("Sure ?");
		if (valid) {
			todos.removeChild(obj.target);
			saveCookie("ft_list");
		}
	});
	todos.insertBefore(todo, todos.firstChild);
	saveCookie("ft_list");
	});
};
