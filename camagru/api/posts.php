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
			if (!Utils::is_base64($img)) {
				header("42", true, 400);
				return ;
			}

			// get the user input and the mask
			$img = base64_decode($img);
			$mask = file_get_contents('../styles/img/' . $vars['mask'] . '.png');

			// verify that is an image
			if (!imagecreatefromstring($img)) {
				header("42", true, 400);
				return ;
			}

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
		case "retrieve" : {
			// get post from the user if asked
			if (!isset($_GET['author'])) {
				$posts = Post::fromAuthor($_SESSION['user']);
				// if he want, we can send him only few
				if (isset($_GET['offset']) && isset($_GET['length'])) {
					$posts = array_slice($posts, $_GET['offset'], $_GET['length']);
				}
			}
			else if ($_GET['author'] === "all" && isset($_GET['page'])) {
				$posts = Post::queryPage($_GET['page']);
			}

			// send it
			header("Content-Type: application/json", true, 200);
			echo json_encode($posts);
			break ;
		}
		case "delete" : {
			// verify the input
			if (!isset($_GET['post'])) {
				header("42", true, 400);
				return ;
			}
			// query that post
			$post = Post::query($_GET['post']);
			// if null, return a 404 not found
			if ($post == null) {
				header("42", true, 404);
				return ;
			}
			// if its not him the author of the post
			if ($post->author !== $_SESSION['user']) {
				header("42", true, 401);
				return ;
			}
			// else delete the post
			$post->delete();
			break ;
		}
		default : {
			header("42", true, 400);
		}
	}

?>
