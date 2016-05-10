/* global Materialize */
/* global $ */

$(document).ready(function(){
	$('.button-collapse').sideNav();
	$('.parallax').parallax();
	
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
				
				$.post("/signin", { mail: mail, pwd: pwd})
				.done(function(data) {
					console.log( data );
				})
				.fail(function( error ) {
					Materialize.toast("Wild error code appear " + error.status + " " + error.responseText, 3000, 'red lighten-1');
					$('#progress_login').hide();
				});
			}
			
			
			
			
			event.preventDefault();
	});
});