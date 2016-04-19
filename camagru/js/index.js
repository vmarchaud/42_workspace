// Trigger code for modal
window.onload = function() {

    if (window.location.hash.indexOf('#login') != -1)
        document.getElementById("login").style.display = "block";
    else if (window.location.hash.indexOf('#register') != -1)
        document.getElementById("register").style.display = "block";

	var buttons = document.getElementsByClassName("close");
	for(var i = 0; i < buttons.length; i++) {
		buttons[i].addEventListener("click", function() {
	        document.getElementById("register").style.display = "none";
		    document.getElementById("login").style.display = "none";
	    });
	}
};
