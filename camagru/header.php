<?PHP
	session_start();
?>

<html>
	<head>
		<meta charset="utf-8">
		<link rel="stylesheet" href="styles/css/main.css" charset="utf-8">
		<script type="text/javascript" src="js/index.js"></script>
		<title>Instagrumme</title>
	</head>
	<body>
		<div class="modal" id="login">
			<div class="modal-content">
			  <div class="modal-header">
			    <span class="close">×</span>
			    <h2>Login Modal</h2>
			  </div>
			  <div class="modal-body">
  					<label for="mail">Email</label>
  					<input type="email" name="mail" placeholder="email" /><br />
  					<label for="password">Password</label>
  					<input type="password" name="password" placeholder="password"/><br />
			  </div>
			  <div class="modal-footer">
			  		<button>Login</button>
	  				<button>Register</button/>
			  </div>
			</div>
		</div>
		<div class="modal" id="register">
			<div class="modal-content">
			  <div class="modal-header">
			    <span class="close">×</span>
			    <h2>Register Modal</h2>
			  </div>
			  <div class="modal-body">
  					<label for="mail">Email</label>
  					<input type="email" name="mail" placeholder="email" /><br />
	    			<label for="name">Name</label>
	    			<input type="text" name="name" placeholder="name" /><br />
  					<label for="password">Password</label>
  					<input type="password" name="password" placeholder="password"/><br />
  					<label for="password">Confirmation</label>
  					<input type="password" name="passwordConfirm" placeholder="password"/><br />
			  </div>
			  <div class="modal-footer">
			  		<button>Register me !</button>
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
