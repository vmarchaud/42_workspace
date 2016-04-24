<?php
	if (!$_GET['action']) {
		header("42", true, 400);
		return ;
	}

	session_start();
	require_once '../class/Database.class.php';
	require_once '../class/User.class.php';

	switch($_GET['action']) {
		case "retrieve" : {
			header("Content-Type: application/json", true, 200);
			$content = file_get_contents("../config/masks.json");
			echo $content;
			break ;
		}
		default : {
			header("42", true, 400);
		}
	}

?>
