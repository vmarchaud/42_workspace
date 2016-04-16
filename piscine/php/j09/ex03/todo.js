	

	function insert_todo(text, first) {
		var todos = $("#ft_list");
		var todo = document.createElement("div");
		todo.innerHTML = text;
		$(todo).click( function(obj) {
			var valid = confirm("Sure ?");
			if (valid) {
				$(obj.currentTarget).remove();
				$.post("ex03/delete.php", { todo: obj.currentTarget.innerHTML });
			}
		});
		todos.prepend(todo);
	}

	$(document).ready(function() {
		
		$.get("ex03/select.php", function(data, status) {
			console.log(data);
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
		$.post("ex03/insert.php", { todo: input});
	});
