<?PHP
	session_start();
?>

<html>
	<head>
		<meta charset="utf-8">
		<link rel="stylesheet" href="styles/css/main.css" charset="utf-8">
		<script type="text/javascript" src="js/index.js"></script>
		<script type="text/javascript" src="js/ft_ajax.js"></script>
		<title>Instagrumme</title>
	</head>
	<body>
		<div class="modal" id="login">
			<div class="modal-content">
			  <div class="modal-header">
			    <span class="close">×</span>
			    <h2>Login Modal</h2>
			  </div>
			  <div id="login_modal" class="modal-body">
  					<label for="mail">Email</label>
  					<input type="email" name="login_mail" placeholder="email" /><br />
  					<label for="password">Password</label>
  					<input type="password" name="login_password" placeholder="password"/><br />
			  </div>
			  <div class="modal-footer">
			  		<button id="login_button">Login</button>
	  				<button id="open_register">Register</button/>
			  </div>
			</div>
		</div>
		<div class="modal" id="register">
			<div class="modal-content">
			  <div class="modal-header">
			    <span class="close">×</span>
			    <h2>Register Modal</h2>
			  </div>
			  <div id="register_modal" class="modal-body">
  					<label for="mail">Email</label>
  					<input type="email" name="mail" placeholder="email" /><br />
	    			<label for="name">Name</label>
	    			<input type="text" name="name" placeholder="name" /><br />
  					<label for="password">Password</label>
  					<input type="password" name="password" placeholder="password"/><br />
  					<label for="password">Confirm</label>
  					<input type="password" name="passwordConfirm" placeholder="password"/><br />
			  </div>
			  <div class="modal-footer">
			  		<button id="register_button">Register me !</button>
			  </div>
			</div>
		</div>
		<div class="header">
			<div class="container">
				<div class="left">
					<?php if ($_SESSION['user']) { echo '<span>Bonjour, '. $_SESSION['user_name'] .'</span>'; } ?></span>
				</div>
				<div class="right">
				<?php
					if (!$_SESSION['user']) {
						echo '<a onclick="document.getElementById(\'login\').style.display = \'block\';" href="#">Login</a>';
						echo '<a onclick="document.getElementById(\'register\').style.display = \'block\';" href="#">Register</a>';
					} else {
						echo '<a href="user.php">Account</a>';
						echo '<a href="#">Logout</a>';
					}
				?>
				</div>
			</div>
		</div>
