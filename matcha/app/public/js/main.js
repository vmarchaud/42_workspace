/* global GMaps */
/* global Materialize */
/* global $ */

var map;
var image_upload = null;
// register socket io
var socket = io();
var chat_users = {};
var state_user_list = Cookies.get('user_list');

if (state_user_list == "false") {
	$('.chat_body').slideToggle(0);
}

socket.on('new_message', function(data) {
	$('#audio-popup').trigger('play');
	if (!$('#' + data.chat).is('div')) {
		//query the history of this chat
		socket.emit('get_history', { 'id': data.chat });
		
		// add the box
		var html = '<div id=' + data.chat + ' class="msg_box">';
		html+= '<div class="msg_head">' + data.user + '<i style="float: right;" class="material-icons">close</i></div>';
		html += '<div class="msg_wrap"><div class="msg_body"></div>';
		html += '<div class="msg_footer"><textarea class="msg_input" rows="4"></textarea></div></div>';
		$('.chat_box').before(html);
		
		// handle keypress on input
		$('.msg_input').keypress(function(event) {
			if (event.keyCode != 13) return ;
				 
			event.preventDefault();
			var msg = $(this).val();
			$(this).val('');
			if(msg != '') {
				// emit the message
				var chatID = $($(this).parent().parent().parent()).attr('id');
				
				socket.emit('new_message', {
					'chat': chatID,
					'msg': msg
				});
				
				// add the html
				$($(this).parent().parent().children()[0]).append('<div class="msg_b">'+ msg +'</div>');
				// scroll to bottom
				$($(this).parent().parent().children()[0]).scrollTop($($(this).parent().parent().children()[0])[0].scrollHeight);
			}
		});
		
		// handle close window
		$('.msg_head').click(function(event){
			$(this).parent().remove();
		});
	} else {
		var body = $('#' + data.chat + ' > .msg_wrap').children()[0];
		// add the msg
		$(body).append('<div class="msg_a">'+ data.msg +'</div>');
		// scroll to bottom
		$(body).scrollTop($(body)[0].scrollHeight);
	}
});

socket.on('alerts', function(data) {
	$('#alert_nbr').html(data.nbr);
});

socket.on('new_alerts', function(data) {
	var current = parseInt($('#alert_nbr').html());
	$('#alert_nbr').html(current + 1 + "");
});

socket.on('get_history', function(data) {
	if (!$('#' + data.chat).is('div')) return ;
	
	var body = $('#' + data.chat + ' > .msg_wrap').children()[0];
	for (var i = 0; i < data.msgs.length; i++) {
		if (data.msgs[i].user === data.user)
			$(body).prepend('<div class="msg_b">'+ data.msgs[i].msg +'</div>');
		else 
			$(body).prepend('<div class="msg_a">'+ data.msgs[i].msg +'</div>');
	}
	$(body).scrollTop($(body)[0].scrollHeight);
});

// when we got the user list
socket.on('user_list', function (data) {
	for(var i = 0; i < data.length; i++) {
		chat_users[data[i].id] = data[i];
		var state = data[i].last_visit == "0000-00-00 00:00:00" ? "online" : "offline";
		$('.chat_body').append('<div chatID="' + data[i].id + '"class="user_' + state +' chat_click">' + data[i].firstname + ' ' + data[i].lastname + ' </div>');
	}
	
	$('.chat_click').click(function (event) {
		var id = $(this).attr('chatID');
		// if the box doesnt already exist
		if (!$('#' + id).is('div')) {
			//query the history of this chat
			socket.emit('get_history', { 'id': id });
			
			// add the box
			var html = '<div id=' + id + ' class="msg_box">';
			html+= '<div class="msg_head">' + event.target.innerHTML + '<i style="float: right;" class="material-icons">close</i></div>';
			html += '<div class="msg_wrap"><div class="msg_body"></div>';
			html += '<div class="msg_footer"><textarea class="msg_input" rows="4"></textarea></div></div>';
			$('.chat_box').before(html);
			
			// handle keypress on input
			$('.msg_input').keypress(function(event) {
				if (event.keyCode != 13) return ;
				 
				event.preventDefault();
				var msg = $(this).val();
				$(this).val('');
				if(msg != '') {
					// emit the message
					var chatID = $($(this).parent().parent().parent()).attr('id');
					
					socket.emit('new_message', {
						'chat': chatID,
						'msg': msg
					});
					
					// add the html
					$($(this).parent().parent().children()[0]).append('<div class="msg_b">'+ msg +'</div>');
					// scroll to bottom
					$($(this).parent().parent().children()[0]).scrollTop($($(this).parent().parent().children()[0])[0].scrollHeight);
				}
			});
				
			// handle close window
			$('.msg_head').click(function(event){
				$(this).parent().remove();
			});
		}
	})
});


// used to clear array
Array.prototype.clean = function(deleteValue) {
  for (var i = 0; i < this.length; i++) {
    if (this[i] == deleteValue) {         
      this.splice(i, 1);
      i--;
    }
  }
  return this;
};

$(document).ready(function(){
	
	$('.button-collapse').sideNav();
	$('.parallax').parallax();
	
	// Login form
	$("#login_btn").click(function (event) {
			var mail = $('#email_login').val();
			var pwd = $('#password_login').val();
			
			if (mail.length == 0 || pwd.length ==0) 
				Materialize.toast("You must fill all field.", 3000, 'red lighten-1');
			else if (!mail.match(/[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?/))
				Materialize.toast("This mail is not valid !", 3000, 'red lighten-1');
			else if (!pwd.match(/^[a-zA-Z0-9!@#$%^&*]{8,30}$/)) 
				Materialize.toast("Your password must be valid (min 8 chars).", 3000, 'red lighten-1');
			else {
				// show progress bar
				$('#progress_login').show();
				
				$.post("/auth/signin", { mail: mail, pwd: pwd})
				.done(function(data) {
					Materialize.toast("Yeah ! You are now connected !", 2500, 'green lighten-1');
					$('#progress_login').hide();
					setTimeout(function() {
						location.reload(true);
					}, 1000);
					
				})
				.fail(function( error ) {
					if (error.status == 404)
						Materialize.toast("Our system didnt recognize this mail with this password.", 3000, 'red lighten-1');
					else
						Materialize.toast("Wild error code appear " + error.status + " " + error.responseText, 3000, 'red lighten-1');
					$('#progress_login').hide();
				});
			}
			event.preventDefault();
	});
	
	// Login form
	$("#submit_signup").click(function (event) {
			var mail = $('#email_signup').val();
			var pwd = $('#password_signup').val();
			var pwdConfirm = $('#passwordConfirm_signup').val();
			var firstname = $('#firstname_signup').val();
			var lastname = $('#lastname_signup').val();
			
			if (mail.length == 0 || pwd.length ==0 || pwdConfirm == 0 || firstname == 0 || lastname == 0) 
				Materialize.toast("You must fill all fields.", 3000, 'red lighten-1');
			else if (pwd !== pwdConfirm) 
				Materialize.toast("The passwords doesnt matchs.", 3000, 'red lighten-1');
			else if (!mail.match(/[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?/))
				Materialize.toast("This mail is not valid !", 3000, 'red lighten-1');
			else if (!pwd.match(/^[a-zA-Z0-9!@#$%^&*]{8,30}$/)) 
				Materialize.toast("Your password must be valid (min 8 chars).", 3000, 'red lighten-1');
			else {
				// show progress bar
				$('#progress_signup').show();
				
				$.post("/auth/signup", { 'mail': mail, 'pwd': pwd, 'firstname': firstname, 'lastname': lastname})
				.done(function(data) {
					Materialize.toast("Welcome ! You have been registered successfuly", 3000, 'green lighten-1');
					$('#progress_signup').hide();
					
				})
				.fail(function( error ) {
					if (error.status == 404)
						Materialize.toast("Our system didnt recognize this mail with this password.", 3000, 'red lighten-1');
					else
						Materialize.toast("Wild error code appear " + error.status + " " + error.responseText, 3000, 'red lighten-1');
					$('#progress_signup').hide();
				});
			}
			event.preventDefault();
	});
	
	
    $('#gender_profile').material_select();
	
	// Update gender
	$( "#gender_profile" ).change(function() {
		// Get the value
		var selected = $( "#gender_profile" ).find(":selected").text();
		// If he didnt select
		if (selected === "Choose") {
			Materialize.toast("You need to choose MEN or WOMEN to update your gender.", 3000, 'red lighten-1');
		}
		// Else update the data
		else {
			$.post("/me/update", { 'type': "gender", 'data': selected}).done(function(data) {
				Materialize.toast("Your profile have been updated !", 2000, 'green lighten-1');
			}).fail(function( error ) {
				Materialize.toast("Wild error code appear " + error.status + " " + error.responseText, 2000, 'red lighten-1');
			});
		}
	});
	
	// Update the mail
	$( "#email_profile" ).change(function() {
		// Get the value
		var selected = $( "#email_profile" ).val();
		// If he put an invalid data
		if (selected.length == 0 || !selected.match(/[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?/)) {
			Materialize.toast("You need to put a valid email to change it.", 3000, 'red lighten-1');
		}
		// Else update the data
		else {
			$.post("/me/update", { 'type': "mail", 'data': selected}).done(function(data) {
				Materialize.toast("Your profile have been updated !", 2000, 'green lighten-1');
			}).fail(function( error ) {
				Materialize.toast("Wild error code appear " + error.status + " " + error.responseText, 2000, 'red lighten-1');
			});
		}
	});
	
	// Update the name
	$( "#firstname_profile" ).change(function() {
		// Get the value
		var selected = $( "#firstname_profile" ).val();
		// If he put an invalid data
		if (selected.length == 0) {
			Materialize.toast("You need to put a valid name to change it.", 3000, 'red lighten-1');
		}
		// Else update the data
		else {
			$.post("/me/update", { 'type': "firstname", 'data': selected}).done(function(data) {
				Materialize.toast("Your profile have been updated !", 2000, 'green lighten-1');
			}).fail(function( error ) {
				Materialize.toast("Wild error code appear " + error.status + " " + error.responseText, 2000, 'red lighten-1');
			});
		}
	});
	
	// Update the name
	$( "#lastname_profile" ).change(function() {
		// Get the value
		var selected = $( "#lastname_profile" ).val();
		// If he put an invalid data
		if (selected.length == 0) {
			Materialize.toast("You need to put a valid name to change it.", 3000, 'red lighten-1');
		}
		// Else update the data
		else {
			$.post("/me/update", { 'type': "lastname", 'data': selected}).done(function(data) {
				Materialize.toast("Your profile have been updated !", 2000, 'green lighten-1');
			}).fail(function( error ) {
				Materialize.toast("Wild error code appear " + error.status + " " + error.responseText, 2000, 'red lighten-1');
			});
		}
	});
	
	
	$('#orientation_profile').material_select();
	
	// Update orientation
	$( "#orientation_profile" ).change(function() {
		// Get the value
		var selected = $( "#orientation_profile" ).find(":selected").text();
		
		$.post("/me/update", { 'type': "orientation", 'data': selected}).done(function(data) {
			Materialize.toast("Your profile have been updated !", 2000, 'green lighten-1');
		}).fail(function( error ) {
			Materialize.toast("Wild error code appear " + error.status + " " + error.responseText, 2000, 'red lighten-1');
		});
		
	});
	
	// Open new tags modal
	$("#add_tags").click(function (event) {
		$('#add_tags_modal').openModal();
	});
	
	// submit a new tag
	$("#submit_new_tags").click(function (event) {
		var value = $("#new_tag").val();
		
		if (value.length <= 1 || value.length > 30) {
			Materialize.toast("A valid tag must have between 2 and 30 chars", 2000, 'red lighten-1');
		} else if (value.indexOf(' ') != -1) {
			Materialize.toast("A valid tag doesnt have space in it", 2000, 'red lighten-1');
		} else {
			$('#progress_new_tag').show();
			$.post("/me/tag/add", { 'tag': value }).done(function(data) {
				Materialize.toast("Tag has been successfuly added !", 2000, 'green lighten-1');
				$('#progress_new_tag').hide();
				setTimeout(function() {
					location.reload(true);
				}, 1000);
			}).fail(function( error ) {
				if (error.status == 409)
					Materialize.toast("You already have this tag set in your profile", 2000, 'red lighten-1');
				else
					Materialize.toast("Wild error code appear " + error.status + " " + error.responseText, 2000, 'red lighten-1');
				$('#progress_new_tag').hide();
			});
		}
		event.preventDefault();
	});
	
	// Update the bio
	$( "#bio_profile" ).change(function() {
		// Get the value
		var selected = $( "#bio_profile" ).val();
		// If he put an invalid data
		if (selected.length > 242) {
			Materialize.toast("Your bio must have maximum 242 chars.", 3000, 'red lighten-1');
		}
		// Else update the data
		else {
			$.post("/me/update", { 'type': "bio", 'data': selected }).done(function(data) {
				Materialize.toast("Your profile have been updated !", 2000, 'green lighten-1');
			}).fail(function( error ) {
				Materialize.toast("Wild error code appear " + error.status + " " + error.responseText, 2000, 'red lighten-1');
			});
		}
	});
	
    // Update the location of the user
	$( "#update_loc" ).click(function() {
		GMaps.geolocate({
			success: function(position) {
				map.setCenter(position.coords.latitude, position.coords.longitude);
				$.post("/me/update", { 'type': "location", "data": position.coords.latitude + "," + position.coords.longitude }).done(function(data) {
					Materialize.toast("Your location has been successfuly updated", 2000, 'green lighten-1');
				});
			},
			error: function(error){
				$.post("/me/update", { 'type': "location", "data": "refused" }).done(function(data) {});
			}
		});
	});
    
    $( " #image_input ").change(function(event) {
        var file = event.target.files[0];
		var reader = new FileReader();
		reader.addEventListener("load", function (event) {
			image_upload = reader.result;
		});
	   reader.readAsDataURL(file);
    });
    
    // add a image
	$( "#submit_new_image" ).click(function(event) {
        
		// If he put an invalid data
		if (image_upload == null) {
			Materialize.toast("You must choose a image to upload", 3000, 'red lighten-1');
		}
		// Else update the data
		else {
            $.ajax({
               url:  "/me/image/add",
               type: "PUT",
               data: { 'img': image_upload }
            }).done(function(data) {
				Materialize.toast("Your image has been succesfuly added !", 2000, 'green lighten-1');
			    setTimeout(function() {
					location.reload(true);
				}, 1000);
            }).fail(function( error ) {
				Materialize.toast("Wild error code appear " + error.status + " " + error.responseText, 2000, 'red lighten-1');
			});
		}
        
        event.preventDefault();
	});
	
	// search user
	$("#search_user").change(function(event) {
		var input = $("#search_user").val();
		
		// reset already present
		$('#collection_search').hide();
		$("#collection_search").empty();
		
		if (input.length < 2) {
			Materialize.toast("You must write at least 2 chars to search someome", 2000, 'red lighten-1');
			return ;
		}
		
		$('#progress_search_user').show();
		
		 $.post("/search/byName", { 'input': input } ).done(function(data) {
			$('#collection_search').show();
				console.log(data);
			for(var i = 0; i < data.length; i++) {
				if (data[i].picture == undefined || data[i].picture.length == 0) {
					data[i].picture = "/img/default_avatar.jpg";
				}
				
				$('<a href="/profile/' + data[i].id + '" class=" collection-item search_user"> <img src="' + data[i].picture +'">' 
				+ '<p>' + data[i].firstname + ' ' + data[i].lastname + '</p></a>').appendTo("#collection_search");
			}
			$('#progress_search_user').hide();
		}).fail(function( error ) {
			if (error.status == 404) 
				Materialize.toast("No user has been found with this name", 2000, 'red lighten-1');
			else 
				Materialize.toast("Wild error code appear " + error.status + " " + error.responseText, 2000, 'red lighten-1');
			$('#progress_search_user').hide();
			$('#collection_search').hide();
		});
		
		event.preventDefault();
	});
	
	// handle reporting
    $('#report_cause').material_select();
	
    $('#send_report').click(function(event) {
		event.preventDefault();
		
		var cause = $("#report_cause").val();
		// get user id in url
		var path = window.location.pathname.split('/').clean('');
		var user = path[path.length - 1];
		 $.post("/user/report", { 'id': user, 'reason': cause } ).done(function(data) {
			Materialize.toast("You have successfuly reported this user, thanks !", 2000, 'green lighten-1');
			
			setTimeout(function() {
					$('#report_modal').closeModal();
			}, 1000);
		}).fail(function( error ) {
			if (error.status == 404) 
				Materialize.toast("You are trying to report an user that doesnt exist", 2000, 'red lighten-1');
			else if (error.status == 400) 
				Materialize.toast("Are you trying to report yourself ?", 2000, 'red lighten-1');
			else 
				Materialize.toast("Wild error code appear " + error.status + " " + error.responseText, 2000, 'red lighten-1');
			setTimeout(function() {
					$('#report_modal').closeModal();
			}, 1000);
		});
	});
	
	// handle blocking
	$('#block_user').click(function() {
		// get user id in url
		var path = window.location.pathname.split('/').clean('');
		var user = path[path.length - 1];
		
		$.post("/user/block", { 'id': user } ).done(function(data) {
			Materialize.toast("Operation successfull !", 2000, 'green lighten-1');
			
			setTimeout(function() {
				location.reload(true);
			}, 1000);
		}).fail(function( error ) {
			if (error.status == 400) 
				Materialize.toast("Are you trying to block yourself ?", 2000, 'red lighten-1');
			else 
				Materialize.toast("Wild error code appear " + error.status + " " + error.responseText, 2000, 'red lighten-1');
		});
	});
	
	// handle matching
	$('#match_user').click(function() {
		// get user id in url
		var path = window.location.pathname.split('/').clean('');
		var user = path[path.length - 1];
		
		$.post("/user/match", { 'id': user } ).done(function(data) {
			Materialize.toast("Operation successfull !", 2000, 'green lighten-1');
			
			setTimeout(function() {
				location.reload(true);
			}, 1000);
		}).fail(function( error ) {
			if (error.status == 400) 
				Materialize.toast("Are you trying to match yourself ?", 2000, 'red lighten-1');
			else 
				Materialize.toast("Wild error code appear " + error.status + " " + error.responseText, 2000, 'red lighten-1');
		});
	});
	
	// handle chat
	$('.chat_head').click(function(){
		$('.chat_body').slideToggle('slow');
		if (state_user_list === "true")
			state_user_list = "false";
		else
			state_user_list = "true";
		Cookies.set('user_list', state_user_list);
	});
	
	// handle age interval
	var age_slider = document.getElementById('age_interval');
      noUiSlider.create(age_slider, {
       start: [18, 80],
       connect: true,
       step: 1,
       range: {
         'min': 18,
         'max': 80
       },
       format: wNumb({
         decimals: 0
       })
      });
	var score_slider = document.getElementById('score_interval');
      noUiSlider.create(score_slider, {
       start: [0, 100],
       connect: true,
       step: 1,
       range: {
         'min': 0,
         'max': 100
       },
       format: wNumb({
         decimals: 0
       })
      });
	var distance_slider = document.getElementById('distance_interval');
      noUiSlider.create(distance_slider, {
       start: [20, 80],
       connect: true,
       step: 1,
       range: {
         'min': 0,
         'max': 100
       },
       format: wNumb({
         decimals: 0
       })
      });
	  
	  $('#select_tags').material_select();
	  
	  // search user
	$("#search_user").change(function(event) {
		event.preventDefault();
		search_user();
	});
	$("#select_tags").change(function(event) {
		event.preventDefault();
		search_user();
	});
	
	distance_slider.noUiSlider.on('change', function () {
		search_user();
	});
	age_slider.noUiSlider.on('change', function () {
		search_user();
	});
	score_slider.noUiSlider.on('change', function () {
		search_user();
	});
	
	
	function search_user() {
		var name = $("#search_user").val() || "";
		var age_min = age_slider.noUiSlider.get()[0], age_max = age_slider.noUiSlider.get()[1];
		var distance_min = distance_slider.noUiSlider.get()[0], distance_max = distance_slider.noUiSlider.get()[1];
		var score_min = score_slider.noUiSlider.get()[0], score_max = score_slider.noUiSlider.get()[1];
		var interests = $("#select_tags").val();
			
		// reset already present
		$('#collection_search').hide();
		$("#collection_search").empty();
			
		$('#progress_search_user').show();
			
		$.post("/search", { 'name': name, 'age_min': age_min, 'age_max': age_max,
				'distance_min': distance_min, 'distance_max': distance_max, 'interests': interests} ).done(function(data) {
			$('#collection_search').show();
			for(var i = 0; i < data.length; i++) {
				if (data[i].picture == undefined || data[i].picture.length == 0) {
					data[i].picture = "/img/default_avatar.jpg";
				}
					
				$('<a href="/profile/' + data[i].id + '" class=" collection-item search_user"> <img src="' + data[i].picture +'">' 
				+ '<p>' + data[i].firstname + ' ' + data[i].lastname + '</p></a>').appendTo("#collection_search");
			}
			$('#progress_search_user').hide();
		}).fail(function( error ) {
			if (error.status == 404) 
				Materialize.toast("No user has been found with this name", 2000, 'red lighten-1');
			else 
				Materialize.toast("Wild error code appear " + error.status + " " + error.responseText, 2000, 'red lighten-1');
			$('#progress_search_user').hide();
			$('#collection_search').hide();
		});
			
		event.preventDefault();
	}
});

$( "#map_profile" ).ready(function() {
	if (!$( "#map_profile" ).is("div"))
		return ;
		
	var loc = $( "#map" ).attr("loc");
	if (loc !== undefined) {
		if (loc.length == 0) {
			Materialize.toast("This user didnt set his location", 2000, 'red lighten-1');
			map = new GMaps({
				el: '#map',
				lat: 48.866667,
				lng: 2.333333,
				zoom: 0
			});
		}
		else {
			var loc = loc.split(",");
			map = new GMaps({
				el: '#map',
				lat: loc[0],
				lng: loc[1]
			});
		}
		return ;
	}
		
	$.post("/me/retrieve", { "type": "location" }).done(function(data) {
		var loc = data.location.split(",");
		map = new GMaps({
			el: '#map',
			lat: loc[0],
			lng: loc[1]
		});
	}).fail(function( error ) {
	 	map = new GMaps({
			el: '#map',
			lat: 48.866667,
			lng: 2.333333,
			zoom: 0
		});
		Materialize.toast("Please accept the localization demand", 2000, 'green lighten-1');
		GMaps.geolocate({
			success: function(position) {
				map.setCenter(position.coords.latitude, position.coords.longitude);
				$.post("/me/update", { 'type': "location", "data": position.coords.latitude + "," + position.coords.longitude }).done(function(data) {
					Materialize.toast("Your location has been successfuly updated", 2000, 'green lighten-1');
				});
			},
			error: function(error) {
				$.post("/me/update", { 'type': "location", "data": "refused" }).done(function(data) {});
			}
		});
		
	});
});

function delete_image(obj) {
    // if the user want to delete an image
      var id =  $( obj ).attr("img");
       
        var state = confirm("Are you sure that you want to delete this image ?");
        
        if (!state)
            return ;
        
        $.post("/me/image/delete", { 'img': id }).done(function(data) {
			Materialize.toast("This image has been successfuly deleted !", 2000, 'green lighten-1');
	       $( obj ).closest("li").remove();
		}).fail(function( error ) {
			Materialize.toast("Wild error code appear " + error.status + " " + error.responseText, 2000, 'red lighten-1');
		});
}

function favorite_image(obj) {
    // if the user want to delete an image
      var id =  $( obj ).attr("img");
       
        var state = confirm("Are you sure that you want make this image your profile picture ?");
        
        if (!state)
            return ;
        
        $.post("/me/image/favorite", { 'img': id }).done(function(data) {
			Materialize.toast("This image is now your profile picture !", 2000, 'green lighten-1');
		}).fail(function( error ) {
			Materialize.toast("Wild error code appear " + error.status + " " + error.responseText, 2000, 'red lighten-1');
		});
}

function delete_chip(obj) {
	var chip = $(obj).closest(".chip");
	var id = chip.attr("id");
	
	var state = confirm("Are you sure that you want to delete this tag ?");
	
	if (!state)
		return ;
		
	$.post("/me/tag/delete", { 'tag': id }).done(function(data) {
			Materialize.toast("Tag has been successfuly deleted !", 2000, 'green lighten-1');
			chip.remove();
		}).fail(function( error ) {
			if (error.status == 409)
				Materialize.toast("You already have this tag set in your profile", 2000, 'red lighten-1');
			else
				Materialize.toast("Wild error code appear " + error.status + " " + error.responseText, 2000, 'red lighten-1');
			$('#progress_new_tag').hide();
		});
}

function load_alerts() {
	// empty the alert list
	$('#alerts_list').empty();
	
	$.get("/me/alert").done(function(data) {
			// add the alert to the list
			for(var i = 0; i < data.length; i++) {
				var active = data[i].shown === 0 ? "active" : "";
				$('#alerts_list').append('<a id="' + data[i].id + '" class="collection-item ' + active + '">' +
						 data[i].msg +'<span class="badge">' + data[i].date + '</span></a>');
			}
			
			$('#progress_alerts').hide();
			// for each not seen setup hover
			$('#alerts_list').children(".active").hover(function(event) {
				// he saw the alert
				socket.emit('alert_shown', {
					id: $(event.target).attr('id')
				});
				
				if ($(event.target).hasClass('active')) {
					// update the nbr of alert
					var current = parseInt($('#alert_nbr').html());
					$('#alert_nbr').html((current - 1) + "");
				}
				
				$(event.target).removeClass("active");
			});
		}).fail(function( error ) {
			if (error.status == 401)
				Materialize.toast("Who are you ?", 2000, 'red lighten-1');
			else
				Materialize.toast("Wild error code appear " + error.status + " " + error.responseText, 2000, 'red lighten-1');
			$('#progress_alerts').hide();
		});
}


function load_visits() {
	$('#progress_visits').show();
	// get user id in url
	var path = window.location.pathname.split('/').clean('');
	var user = path[path.length - 1];
		
	// empty the alert list
	$('#visits_list').empty();
	
	$.post("/user/visit", { id: user }).done(function(data) {
		
		// add the alert to the list
		for(var i = 0; i < data.length; i++) {
			$('#visits_list').append('<a class="collection-item">' +
					 data[i].user +'<span class="badge">' + data[i].date + '</span></a>');
		}
			
		$('#progress_visits').hide();
		}).fail(function( error ) {
			Materialize.toast("Wild error code appear " + error.status + " " + error.responseText, 2000, 'red lighten-1');
			$('#progress_visits').hide();
		});
}

