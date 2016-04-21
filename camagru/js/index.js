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
		var goodbox = document.getElementsByClassName("goodbox");
		for(var i = 0; i < goodbox.length; i++) {
			modal.removeChild(goodbox[i]);
		}

		// create the div that will be displayed if error or success
		var msg = document.createElement("div");

		// Check that password match
		if (pwd.value !== pwdConfirm.value || pwd.value.length < 6) {
			msg.className  = "errorbox";
			msg.innerHTML = "Passwords does not match or are not valid (min 6 characters).";
			modal.insertBefore(msg, modal.firstChild);
			return ;
		}
		// Check that mail is valid
		else if (!mail.value.match(/[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?/)) {
			msg.className  = "errorbox";
			msg.innerHTML = "You need to use a valid mail.";
			modal.insertBefore(msg, modal.firstChild);
			return ;
		}
		// Check that name is correct
		else if (name.value.length < 3) {
			msg.className  = "errorbox";
			msg.innerHTML = "You need to use a valid name (min 3 characters)";
			modal.insertBefore(msg, modal.firstChild);
			return ;
		}

		// Make the ajax request
		ajax.post("/api/auth.php?action=register", { "mail": mail.value, "name": name.value, "pwd": pwd.value }, function(response) {
			msg.className  = "goodbox";
			msg.innerHTML = "A mail has been sent to your mail to validate your account.";
			modal.insertBefore(msg, modal.firstChild);
			// reset form
			mail.value = "";
			pwd.value = "";
			name.value = "";
			pwdConfirm.value = "";
		}, function (error) {
			// create the error
			msg.className  = "errorbox";
			if (error.status == 409) {
				msg.innerHTML = "The mail you used is already registered for an account";
			} else {
				msg.innerHTML = "A wild error appear (code " + error.status + ")";
			}
			// show it
			modal.insertBefore(msg, modal.firstChild);
		});
	});

	// Login form
	document.getElementById("login_button").addEventListener("click", function() {
		var mail = document.getElementByName("login_mail");
		var pwd = document.getElementByName("login_password");
		var modal = document.getElementById("login_modal");

		// create the div that will be displayed if error or success
		var msg = document.createElement("div");

		// Check that field are valid
		if (pwd.value.length < 6) {
			msg.className  = "errorbox";
			msg.innerHTML = "Password isnt valid (min 6 characters).";
			modal.insertBefore(msg, modal.firstChild);
			return ;
		}
		// Check that mail is valid
		else if (!mail.value.match(/[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?/)) {
			msg.className  = "errorbox";
			msg.innerHTML = "You need to use a valid mail.";
			modal.insertBefore(msg, modal.firstChild);
			return ;
		}

		// Make the ajax request
		ajax.post("/api/auth.php?action=login", { "mail": mail, "pwd": pwd }, function(response) {
			// make the success box
			msg.className  = "goodbox";
			msg.innerHTML = "You have been succesfuly connected !";
			modal.insertBefore(msg, modal.firstChild);
			// reset form
			mail.value="";
			pwd.value="";
			// reload page after 1 sec
			setTimeout(function() {
				location.reload(true);
			}, 1000);

		}, function (error) {
			// create the error
			msg.className  = "errorbox";
			if (error.status == 403) {
				msg.innerHTML = "Either you need to valid the mail account or your account has been deleted";
			} else if (error.status == 404) {
				msg.innerHTML = "This couple of mail/password isnt on";
			} else {
				msg.innerHTML = "A wild error appear (code " + error.status + ")";
			}
			// show it
			modal.insertBefore(msg, modal.firstChild);
		});
	});
};
