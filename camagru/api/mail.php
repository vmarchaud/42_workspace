<?php
	if (!$_GET['type']) {
		header("42", true, 400);
		return ;
	}
	session_start();
	require_once '../class/Database.class.php';
	require_once '../class/User.class.php';

	switch($_GET['type']) {
		case "valid" : {
			// verify that the code exist
			if (!$_GET['code'] || !Utils::is_uuid($_GET['code'])) {
				header("42", true, 400);
				return ;
			}
			// get token for db
			$db = Database::getInstance();
			$stmt = $db->prepare("SELECT * FROM tokens WHERE id=?");
			if ($stmt->execute(array($_GET['code']))) {
				$token = $stmt->fetch();
				// valid user account
				$user = User::query($token['user']);
				$user->state = User::REGISTER;
				$user->update();
				// delete the token
				$stmt = $db->prepare("DELETE FROM tokens WHERE id=?");
				$stmt->execute(array($_GET['code']));
			} else {
				header("42", true, 400);
				return ;
			}
			// redirect him
			header("Location: /index.php");
			break ;
		}
		case "forgot" : {
			// he may come for send a new password to an email.
			if (isset($_GET['email'])) {
				$mail = $_GET['email'];
				// check mail is invalid
				if (!filter_var($mail, FILTER_VALIDATE_EMAIL)) {
					header("42", true, 400);
					return ;
				}
				// verify that the mail is in our database
				$db = Database::getInstance();
				$stmt = $db->prepare("SELECT * FROM users WHERE mail=?");
				$stmt->execute(array($mail));
				if ($stmt->rowCount() == 0) {
					header("42", true, 404);
					return ;
				}
				//get the user
				$stmt->setFetchMode(PDO::FETCH_INTO, new User(null));
				$user = $stmt->fetch();
				// change his password to a random string
				$pwd = Utils::random_string(16);
				$user->password = hash("whirlpool", $user->mail . $pwd);
				$user->update();
				// send the mail
				Utils::sendMail(Utils::FORGOT_TYPE, $user, $pwd);
			}
			// else bad request
			else {
				header("42", true, 400);
				return ;
			}
			break ;
		}
	}

 ?>
