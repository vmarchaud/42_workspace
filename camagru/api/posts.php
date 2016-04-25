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
			if (false) {
				header("42", true, 400);
				return ;
			}
			// get the user input and the mask
			$img = base64_decode($img);
			$mask = file_get_contents('../styles/img/' . $vars['mask'] . '.png');

			// merge image and encode the result
			$output = base64_encode(Utils::mergeImage($img, $mask));
			// create the post
			$post = new Post(array('author' => $_SESSION['user'], 'img' => $output));
			try {
				$post->create();
			} catch (Exception $e) {
				header("42", true, 409);
				return ;
			}

			header("42", true, 201);
			break ;
		}
		default : {
			header("42", true, 400);
		}
	}

?>
