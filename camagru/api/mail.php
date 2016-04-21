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
	}

 ?>
