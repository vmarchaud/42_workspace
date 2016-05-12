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
});