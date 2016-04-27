<?php
	if (!$_GET['action']) {
		header("42", true, 400);
		return ;
	}

	session_start();
	require_once '../class/Database.class.php';
	require_once '../class/User.class.php';

	switch($_GET['action']) {
		case "getname" : {
			if (isset($_GET['id']) && Utils::is_uuid($_GET['id'])) {
				// query the user
				$user = User::query($_GET['id']);
				// if the post doesnt exist
				if ($user == null) {
					header("42", true, 404);
					return ;
				}
				// else return his name
				$ret = array("name" => $user->name);
				header("Content-Type: application/json", true, 200);
				echo json_encode($ret);
			}
			break ;
		}
		default : {
			header("42", true, 400);
		}
	}

?>
