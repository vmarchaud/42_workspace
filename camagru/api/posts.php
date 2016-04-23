<?php
	if (!isset($_GET['action'])) {
		header("42", true, 400);
		return ;
	}

	session_start();
	require_once '../class/Database.class.php';
	require_once '../class/User.class.php';
	require_once '../class/Post.class.php';

	switch($_GET['action']) {
		case "create" : {
			// get put content
			parse_str(file_get_contents("php://input"), $vars);
			// verify that they exist and verify that the img is valid
			if (!isset($vars['img']) || !isset($vars['mask']) || strpos($vars['img'], ',') === false) {
				header("42", true, 400);
				return ;
			}
			$img = explode(',', $vars['img'])[1];
			// if the img is not base64
			if (preg_match('/[^-A-Za-z0-9+/=]|=[^=]|={3,}$/', $img) === false) {
				header("42", true, 400);
				return ;
			}
			$img = base64_decode($img);
			// todo

			break ;
		}
		default : {
			header("42", true, 400);
		}
	}

?>
