	

	function insert_todo(text, first) {
		var todos = $("#ft_list");
		var todo = document.createElement("div");
		todo.innerHTML = text;
		$(todo).click( function(obj) {
			var valid = confirm("Sure ?");
			if (valid) {
				$(obj.currentTarget).remove();
				saveCookie("ft_list");
			}
		});
		if (first)
			todos.prepend(todo);
		else
			todos.append(todo);
	}
	
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
		var todos = $("#ft_list").children();
		var values = [];
		for(var i = 0; i < todos.length; i++) {
			values.push(todos[i].innerHTML);
		}
		var value = values.join("%%%");
		document.cookie = name + "=" + value + ";expires=Thu, 18 Dec 2017 12:00:00 UTC";
	}

	$(document).ready(function() {
		var content = getCookie("ft_list");
		content = content.split("%%%");
		for(var i = 0; i < content.length; i++) {
			insert_todo(content[i], false);
		}
	});	
	
	$("#new").click(function () {
		var input = prompt("Please input the name of todo", "");
		if (input.length == 0)
			return ;
		insert_todo(input, true);
		saveCookie("ft_list");
	});
