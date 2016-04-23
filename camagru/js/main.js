////////////////////////////////////////////////////////////////////////
////							HEADER								////
////////////////////////////////////////////////////////////////////////


function resetBox(modal) {
	// reset all error
	var errors = document.getElementsByClassName("errorbox");
	for(var i = 0; i < errors.length; i++) {
		modal.removeChild(errors[i]);
	}
	// reset all success
	var goodbox = document.getElementsByClassName("goodbox");
	for(var i = 0; i < goodbox.length; i++) {
		modal.removeChild(goodbox[i]);
	}
}

var trigger_header = function() {

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

	// Trigger code for logout button
	var logout = document.getElementById("logout_link");
	if (logout !== undefined && logout != null) {
		logout.addEventListener("click", function () {
			var modal = document.getElementById("login_modal");
			// Make the ajax request
			ajax.get("/api/auth.php?action=logout", null, function(response) {
				// reload the page if success
				location.reload(true);
			}, function (error) {
				console.log(error);
				alert("A wild error appear !");
			});
		});
	}

	// Forgot password form
	document.getElementById("forgot_button").addEventListener("click", function() {
		// reset all box (error/success)
		var modal = document.getElementById("login_modal");
		resetBox(modal);

		// create the div that will be displayed if error or success
		var msg = document.createElement("div");

		// get the mail of the user
		var email = prompt("What was the mail of this account ?");
		if (email.length == 0 || !email.match(/[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?/)) {
			msg.className  = "errorbox";
			msg.innerHTML = "You need to input a valid mail for get it back.";
			modal.insertBefore(msg, modal.firstChild);
			return ;
		}
		// send the request to the backend
		ajax.get("/api/mail.php?type=forgot&email=" + email, null, function(response) {
			msg.className  = "goodbox";
			msg.innerHTML = "A mail has been sent at your mail adress with a new password.";
			modal.insertBefore(msg, modal.firstChild);
		}, function (error) {
			// create the error
			msg.className  = "errorbox";
			if (error.status == 404) {
				msg.innerHTML = "Our system hasnt recognized this adress sorry.";
			} else {
				msg.innerHTML = "A wild error appear (code " + error.status + ")";
			}
			// show it
			modal.insertBefore(msg, modal.firstChild);
		});
	});

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

		// reset all box (error/success)
		resetBox(modal);

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
		var mail = document.getElementsByName("login_mail")[0];
		var pwd = document.getElementsByName("login_password")[0];
		var modal = document.getElementById("login_modal");

		// create the div that will be displayed if error or success
		var msg = document.createElement("div");

		// reset all box (error/success)
		resetBox(modal);

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
		ajax.post("/api/auth.php?action=login", { "mail": mail.value, "pwd": pwd.value }, function(response) {
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
				msg.innerHTML = "This couple of mail/password isnt recognized";
			} else {
				msg.innerHTML = "A wild error appear (code " + error.status + ")";
			}
			// show it
			modal.insertBefore(msg, modal.firstChild);
		});
	});
};


////////////////////////////////////////////////////////////////////////
////							CREATE								////
////////////////////////////////////////////////////////////////////////




var trigger_create = function () {
	var video = document.getElementById("cameraIn");
  	var canvas = document.getElementById("canvas");
  	var takescreen = document.getElementById("takeScreen");
	var out = document.getElementById("cameraOut");
  	var streaming = false;

	var currentMask = null;

	var height = 0;
	var width = 320;

	// load all mask
	var lists = document.getElementById("maskList").childNodes[1];
	ajax.get("/api/masks.php", { "action": "retrieve" }, function (response) {
		var data = JSON.parse(response);
		for(var i = 0; i < data.length; i++) {
			var li = document.createElement("li");
			var img = document.createElement("img");
			img.src = data[i].path;
			img.title = data[i].name;

			img.addEventListener("click", function(event) {
				if (currentMask != null)
					currentMask.style.border = "";
				currentMask = event.target;
				currentMask.style.border = "1px solid red";
				applyMask();
			})

			li.appendChild(img);
			lists.appendChild(li);
		}
	}, function (error) {
		// ignore
	});

	// function used to get the data stream from camera and attach it to a video tag
	function handleCamera(stream) {
		video.src = window.URL.createObjectURL(stream);
	}

	// function used in case of fail
	function handleNoCamera(error) {
		console.log("refuse");
	}

	// get all method to get user camera
	navigator.getUserMedia = navigator.getUserMedia || navigator.webkitGetUserMedia || navigator.mozGetUserMedia || navigator.msGetUserMedia || navigator.oGetUserMedia;
	// if we get the video
	if (navigator.getUserMedia) {
		navigator.getUserMedia({video: true}, handleCamera, handleNoCamera);
	}

	video.addEventListener('canplay', function(ev){
	    if (!streaming) {
	      height = video.videoHeight / (video.videoWidth/ width);
	      canvas.setAttribute('width', width);
	      canvas.setAttribute('height', height);
	      streaming = true;
	    }
  	}, false);

	takescreen.addEventListener("click", function() {
		canvas.width = width;
	    canvas.height = height;
	    canvas.getContext('2d').drawImage(video, 0, 0, width, height);
	    var data = canvas.toDataURL('image/png');
		// send photo to the backend
	});

	//
	function applyMask() {
		if (currentMask == null)
			return ;
		var mask = document.getElementById("mask");
		mask.src = currentMask.src;
		mask.style.display = "block";
	}


};



////////////////////////////////////////////////////////////////////////
////							MASTER								////
////////////////////////////////////////////////////////////////////////

window.onload = function () {
	// trigger all function that are register on load
	if (window.location.href.indexOf('create') != -1)
		trigger_create();
	trigger_header();
};
