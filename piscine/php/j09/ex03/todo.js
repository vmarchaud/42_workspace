	

	function insert_todo(text, first) {
		var todos = $("#ft_list");
		var todo = document.createElement("div");
		todo.innerHTML = text;
		$(todo).click( function(obj) {
			var valid = confirm("Sure ?");
			if (valid) {
				$(obj.currentTarget).remove();
				$.post("delete.php", { todo: obj.currentTarget.innerHTML });
			}
		});
		todos.prepend(todo);
	}

	$(document).ready(function() {
		
		$.get("select.php", function(data, status) {
			if (data) {
				data = data.split('\n');
				for(var i = 0; i < data.length - 1; i++) {
					var value = data[i].split(';');
					insert_todo(value[1], false);
				}
			}
		});	
	});	
	
	$("#new").click(function () {
		var input = prompt("Please input the name of todo", "");
		if (input.length == 0)
			return ;
		insert_todo(input, true);
		$.post("insert.php", { todo: input});
	});
