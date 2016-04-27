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
			if (isset($_GET['id']) && Utils::is_uuid($_GET['id'])) {
				// prepare the request
				$db = Database::getInstance();
				$stmt = $db->prepare("SELECT * FROM likes WHERE post=?");
				// execute
				$stmt->execute(array($_GET['id']));
				// return the count
				$ret = array("count" => $stmt->rowCount());
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
