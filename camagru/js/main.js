////////////////////////////////////////////////////////////////////////
////							HEADER								////
////////////////////////////////////////////////////////////////////////


function resetBox() {
	// reset all error
	var errors = document.getElementsByClassName("errorbox");
	for(var i = 0; i < errors.length; i++) {
		errors[i].parentElement.removeChild(errors[i]);
	}
	// reset all success
	var goodbox = document.getElementsByClassName("goodbox");
	for(var i = 0; i < goodbox.length; i++) {
		goodbox[i].parentElement.removeChild(goodbox[i]);
	}
}

var onload_header = function() {

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
				alert("Error while trying to delete a post. (Error " + error.status + ")");
			});
		});
	}

	// Forgot password form
	document.getElementById("forgot_button").addEventListener("click", function() {
		// reset all box (error/success)
		var modal = document.getElementById("login_modal");
		resetBox();

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
		resetBox();

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
			if (window.location.hash.indexOf("register") != -1)
				window.location.hash = "";
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
			if (window.location.hash.indexOf("login") != -1)
				window.location.hash = "";
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


function onload_create() {
	var video = document.getElementById("cameraIn");
  	var canvas = document.getElementById("canvas");
  	var takescreen = document.getElementById("takeScreen");
	var out = document.getElementById("cameraOut");
  	var streaming = false;

	var currentMask = null;
	var data = null;

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
				takescreen.disabled = false;
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


	var posts = document.getElementById("postsList").childNodes[1];

	function add_post(post, appendFirst) {
		var li = document.createElement("li");
		var img = document.createElement("img");
		var del = document.createElement("button");

		li.id = post.id;
		img.src = "data:image/png;base64," + post.img;
		del.innerHTML = "Delete";
		// If the user want to delete it
		del.addEventListener("click", function (event) {
			var valid = confirm("Sure ?");
			if (!valid) return ;

			// make the request, if it all good, remove the li balise
			ajax.get("/api/posts.php", { "action": "delete", "post": event.target.parentElement.id }, function (response) {
				event.target.parentElement.parentElement.removeChild(event.target.parentElement);
			}, function (error) {
				alert("Error while trying to delete a post. (Error " + error.status + ")");
			});
		});

		li.appendChild(img);
		li.appendChild(del);
		if (appendFirst)
			posts.insertBefore(li, posts.firstChild);
		else
			posts.appendChild(li);
	}

	// load all posts
	ajax.get("/api/posts.php", { "action": "retrieve" }, function (response) {
		var list = JSON.parse(response);
		for(var i = 0; i < list.length; i++) {
			add_post(list[i], false);
		}
		if (list.length == 0) {
			var li = document.createElement("div");
			li.innerHTML = "No post here atm ..";
			posts.parentElement.parentElement.appendChild(li);
		}
	}, function (error) {
		alert("Error while trying to retrieve the masks. (Error " + error.status + ")");
	});

	// get all method to get user camera
	navigator.getUserMedia =  navigator.getUserMedia ||  navigator.webkitGetUserMedia || navigator.mozGetUserMedia || navigator.msGetUserMedia;
	// if we get the video
	if (navigator.getUserMedia) {
		navigator.getUserMedia({video: true},  function (stream) {
			if (navigator.mozGetUserMedia) {
				// cause mozilla est different
			   	video.mozSrcObject = stream;

				// play the video
	  			 video.play();

	  			 // coompute the size of the canvas after a demi second
	  			 setTimeout(function() {
	  				 if (!streaming) {
	  				      height = video.videoHeight / (video.videoWidth/ width);
	  				      canvas.setAttribute('width', width);
	  				      canvas.setAttribute('height', height);
	  				      streaming = true;
	  			    }
	  			}, 500);
			 } else {
			   var vendorURL = window.URL || window.webkitURL;
			   video.src = vendorURL.createObjectURL(stream);
			 }



		}, function (error) {
			var fileinput = document.getElementById("fileinput");
			fileinput.style.display = "block";
		});
	} else {
		var fileinput = document.getElementById("fileinput");
		fileinput.style.display = "block";
	}

	// trigger code for chrome
	video.addEventListener('canplay', function(ev){
	    if (!streaming) {
	      height = video.videoHeight / (video.videoWidth/ width);
	      canvas.setAttribute('width', width);
	      canvas.setAttribute('height', height);
	      streaming = true;
		  video.play();
	    }
  	}, false);

	// Trigger code when clicking on upload
	takescreen.addEventListener("click", function() {
		// the mask must be set
		if (currentMask == null) {
			alert("You must choose a mask to upload a new montage");
			return ;
		}

		// if the input come from camera
		if (streaming) {
			video.style.border = "1px solid red";
			video.pause();
			canvas.width = width;
		    canvas.height = height;
		    canvas.getContext('2d').drawImage(video, 0, 0, width, height);
		    data = canvas.toDataURL('image/png');
		}

		// else it must come from input file
		if (data == null) {
			alert("You must choose an image to upload it");
			return ;
		}

		// send photo to the backend
		ajax.put("/api/posts.php?action=create", { "mask": currentMask.title, "img": data}, function(response) {

			ajax.get("/api/posts.php", { "action": "retrieve", "offset" : 0, "length" : 1 }, function (response) {
				response = JSON.parse(response);
				if (response.length > 0)
					add_post(response[0], true);
			}, function (error) {});

			// play video after one second if the input is camera
			if (streaming) {
				setTimeout(function() {
					video.play();
					video.style.border = "0";
				}, 1000);
			}
		}, function(error) {
			alert("Error while trying to post a new image. (Error " + error.status + ")");
			// play video after one second if the input is camera
			if (streaming) {
				setTimeout(function() {
					video.play();
					video.style.border = "0";
				}, 500);
			}
		});


	});

	// Update the currrent mask
	function applyMask() {
		if (currentMask == null)
			return ;
		var mask = document.getElementById("mask");
		mask.src = currentMask.src;
		mask.style.display = "block";
	}

	document.getElementById('fileinput').addEventListener('change', function(event) {
		var file = event.target.files[0];
		var reader = new FileReader();
		reader.addEventListener("load", function (event) {
			video.setAttribute("poster", reader.result);
			data = reader.result;
		});
		if (file)
			reader.readAsDataURL(file);
	}, false);


};

////////////////////////////////////////////////////////////////////////
////							INDEX								////
////////////////////////////////////////////////////////////////////////

var onload_index = function () {
	var currentPage = 0;
	var posts = document.getElementById("allposts").childNodes[1];

	function add_post(post) {
		var li = document.createElement("li");
		var img = document.createElement("img");

		li.id = post.id;
		li.addEventListener("click", function(event) {
			window.location.replace("/post.php#" + post.id);
		});
		img.src = "data:image/png;base64," + post.img;

		li.appendChild(img);
		posts.appendChild(li);
	}

	function queryPage(page) {
		// remove all child
		while (posts.firstChild) posts.removeChild(posts.firstChild);

		ajax.get("/api/posts.php", { "action": "retrieve", "author" : "all", "page" : currentPage }, function (response) {
			var list = JSON.parse(response);
			for(var i = 0; i < list.length; i++) {
				add_post(list[i]);
			}

			if (list.length == 0) {
				var li = document.createElement("div");
				li.innerHTML = "Its appear that there is no post here ..";
				document.getElementById("allposts").appendChild(li);
			}

			posts.appendChild(document.createElement("br"));

			if (page > 0) {
				var prev = document.createElement("button");
				prev.innerHTML = "Previous";
				prev.style.width = "40%";
				prev.addEventListener("click", function (event) {
					currentPage--;
					queryPage(currentPage);
				});
				posts.appendChild(prev);
			}

			if (list.length == 10) {
				var next = document.createElement("button");
				next.innerHTML = "Next";
				next.style.width = "40%";
				next.addEventListener("click", function (event) {
					currentPage++;
					queryPage(currentPage);
				});
				posts.appendChild(next);
			}
		}, function (error) {
			if (error.status == 404) {
				currentPage--;
				queryPage(currentPage);
				return ;
			}
			alert("Error while trying to retrieve the posts. (Error " + error.status + ")");
		});
	}

	// load all posts
	queryPage(currentPage);

}

////////////////////////////////////////////////////////////////////////
////							POST								////
////////////////////////////////////////////////////////////////////////

var onload_post = function () {
	var post = document.getElementById("post");
	var id = window.location.hash.substring(1, window.location.hash.length);

	ajax.get("/api/posts.php", { "action": "retrieve", "id": id}, function (response) {
		var elem = JSON.parse(response);
		// show image
		var img = document.createElement("img");
		img.src = "data:image/png;base64," + elem.img;
		post.appendChild(img);
		post.appendChild(document.createElement("br"));

		// get the nbr of like
		var like = document.createElement("div");
		ajax.get("/api/likes.php", { "action": "retrieve", "id": elem.id}, function (response) {
			var count = JSON.parse(response).count;
			like.innerHTML = count + " LIKE";
		}, function (error) {
			var count = 0;
			like.innerHTML = count + " LIKE";
			alert("Error while trying to retrieve the post like. (Error " + error.status + ")");
		});

		// show div
		like.className = "like";
		post.appendChild(like);

		// if the user click on it, send the request and update the number
		like.addEventListener("click", function () {
			ajax.get("/api/posts.php", { "action": "like", "id": elem.id}, function (response) {
				var state = JSON.parse(response).state;
				if (state === "ADDED") {
					var count = parseInt(like.innerHTML);
					count++;
					like.innerHTML = count + " LIKE";
				} else if (state === "DELETED") {
					var count = parseInt(like.innerHTML);
					count--;
					like.innerHTML = count + " LIKE";
				}
			}, function (error) {
				if (error.status == 401)
					document.getElementById("login").style.display = "block";
				else
					alert("Error while trying to like/unlike the post. (Error " + error.status + ")");
			});
		});

		// show user and date
		ajax.get("/api/users.php", { "action": "getname", "id": elem.author}, function (response) {
			var user = JSON.parse(response);
			var text = document.createElement("p");
			text.innerHTML = "created by " + user.name + " at " + elem.date;
			post.appendChild(text);
		}, function (error) {
			alert("Error while trying to retrieve the post author. (Error " + error.status + ")");
		});

	}, function (error) {
		alert("Error while trying to retrieve the post. (Error " + error.status + ")");
	});

	// request the comment
	var commentbox = document.getElementById("comments");

	ajax.get("/api/comments.php", { "action": "retrieve", "post": id }, function (response) {
		var comments = JSON.parse(response);
		for(var i = 0; i < comments.length; i++) {
			// add the comment
			var comment = document.createElement("div");
			comment.className = "comment";
			comment.innerHTML = comments[i].content;
			comment.id = comments[i].id;

			commentbox.insertBefore(comment, document.getElementById("newcomment"));

			// get user name and show it
			ajax.get("/api/users.php", { "action": "getname", "id": comments[i].author}, function (response) {
				var user = JSON.parse(response);
				var text = document.createElement("p");
				text.className = "author";
				text.innerHTML = "posted by " + user.name;
				comment.appendChild(text);
			}, function (error) {
				alert("Error while trying to retrieve the comment author. (Error " + error.status + ")");
			}, false);

		}
	}, function (error) {
		alert("Error while trying to retrieve the post author. (Error " + error.status + ")");
	});

	// add a new comment

	var newcomment = document.getElementById("post-comment");
	var content = document.getElementById("comment-content");
	var msgBox = document.createElement("div");

	newcomment.addEventListener("click", function (event) {
		// reset all box (error/success)
		resetBox();

		// if msg is empty
		if (content.value.length === 0) {
			msgBox.className  = "errorbox";
			msgBox.innerHTML = "You must write something to post the a new comment.";
			content.parentElement.insertBefore(msgBox, content);
			return ;
		}
		// make the request
		ajax.put("/api/comments.php?action=create", { "content": content.value, "post": id}, function(response) {
			msgBox.className  = "goodbox";
			msgBox.innerHTML = "You comment has been succesfuly created.";
			content.parentElement.insertBefore(msgBox, content);
			content.value = "";
			setTimeout(function() {
				location.reload(true);
			}, 1000);
		}, function(error) {
			if (error.status == 401) {
			    document.getElementById("login").style.display = "block";
				return ;
			}
			alert("Error while trying to post a new comment. (Error " + error.status + ")");
		});
	});
}
