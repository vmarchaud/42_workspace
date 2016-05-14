/* global Materialize */
/* global $ */

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
	
	
});

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
			if (error.status)
				Materialize.toast("You already have this tag set in your profile", 2000, 'red lighten-1');
			else
				Materialize.toast("Wild error code appear " + error.status + " " + error.responseText, 2000, 'red lighten-1');
			$('#progress_new_tag').hide();
		});
}