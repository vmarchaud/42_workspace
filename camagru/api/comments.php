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
			// get post from the user if asked
			if (!isset($_GET['author']) && !isset($_GET['id'])) {
				$posts = Comment::fromAuthor($_SESSION['user']);
				// if he want, we can send him only few
				if (isset($_GET['offset']) && isset($_GET['length'])) {
					$posts = array_slice($posts, $_GET['offset'], $_GET['length']);
				}
			}
			else if (isset($_GET['post']) && Utils::is_uuid($_GET['post'])) {
				// query comments liked to the post
				$posts = Comment::fromPost($_GET['post']);
				// if there is a problem
				if ($posts == null) {
					header("42", true, 404);
					return ;
				}
				// else just continue to return the posts object
			}
			else {
				// in case of
				header("42", true, 400);
				return ;
			}
			// send it
			header("Content-Type: application/json", true, 200);
			echo json_encode($posts);
			break ;
		}
		default : {
			header("42", true, 400);
		}
	}

?>
