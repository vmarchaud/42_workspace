
window.onload = function() {
	// Trigger code for modal url
    if (window.location.hash.indexOf('#login') != -1)
        document.getElementById("login").style.display = "block";
    else if (window.location.hash.indexOf('#register') != -1)
        document.getElementById("register").style.display = "block";

	// Trigger code for close button
	var buttons = document.getElementsByClassName("close");
	for(var i = 0; i < buttons.length; i++) {
		buttons[i].addEventListener("click", function() {
	        document.getElementById("register").style.display = "none";
		    document.getElementById("login").style.display = "none";
	    });
	}

	// Trigger code for modal button
	document.getElementById("open_register").addEventListener("click", function() {
		document.getElementById("login").style.display = "none";
	    document.getElementById("register").style.display = "block";
	});

	// Register form
	document.getElementById("register_button").addEventListener("click", function() {
		// get all value form
		var mail = document.getElementsByName("mail")[0];
		var name = document.getElementsByName("name")[0];
		var pwd = document.getElementsByName("password")[0];
		var pwdConfirm = document.getElementsByName("passwordConfirm")[0];
		var modal = document.getElementById("register_modal");

		// reset all error
		var errors = document.getElementsByClassName("errorbox");
		for(var i = 0; i < errors.length; i++) {
			modal.removeChild(errors[i]);
		}

		// Check that password match
		if (pwd.value !== pwdConfirm.value || pwd.value.length < 6) {
			var msg = document.createElement("div");
			msg.className  = "errorbox";
			msg.innerHTML = "Passwords does not match or are not valid (min 6 characters).";
			modal.insertBefore(msg, modal.firstChild);
			return ;
		}
		// Check that mail is valid
		else if (!mail.value.match(/[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?/)) {
			var msg = document.createElement("div");
			msg.className  = "errorbox";
			msg.innerHTML = "You need to use a valid mail.";
			modal.insertBefore(msg, modal.firstChild);
			return ;
		}
		// Check that name is correct
		else if (name.value.length < 3) {
			var msg = document.createElement("div");
			msg.className  = "errorbox";
			msg.innerHTML = "You need to use a valid name (min 3 characters)";
			modal.insertBefore(msg, modal.firstChild);
			return ;
		}

			console.log("response");
		// Make the ajax request
		ajax.post("/api/auth.php?action=register", { "mail": mail.value, "name": name.value, "pwd": pwd.value }, function(response) {
			console.log(response);
		}, function (error) {
			console.log(error);
		});
	});

	// Login form
	document.getElementById("login_button").addEventListener("click", function() {
		var mail = document.getElementByName("login_mail");
		var pwd = document.getElementByName("login_password");
		// Make the ajax request
		ajax.post("/api/auth.php?action=login", { "mail": mail, "pwd": pwd }, function(response) {
			console.log(response);
		}, function (error) {
			console.log(error);
		});
	});
};
