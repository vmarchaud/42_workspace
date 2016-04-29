<?php
	if (!$_GET['action']) {
		header("42", true, 400);
		return ;
	}

	session_start();
	require_once '../class/Database.class.php';
	require_once '../class/User.class.php';
	require_once '../class/Comment.class.php';
	require_once '../class/Post.class.php';

	switch($_GET['action']) {
		case "retrieve" : {
			// get post from the user if asked
			if (!isset($_GET['author']) && !isset($_GET['post'])) {
				$posts = Comment::fromAuthor($_SESSION['user']);
				// if he want, we can send him only few
				if (isset($_GET['offset']) && isset($_GET['length'])) {
					$posts = array_slice($posts, $_GET['offset'], $_GET['length']);
				}
			}
			else if (isset($_GET['post']) && Utils::is_uuid($_GET['post'])) {
				// query comments liked to the post
				$posts = Comment::fromPost($_GET['post']);
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
		case "create" : {
			// verify that is logged
			if (!isset($_SESSION['user'])) {
				header("42", true, 401);
				return ;
			}

			// get put content
			parse_str(file_get_contents("php://input"), $vars);
			// verify that they exist and verify that the img is valid
			if (!isset($vars['content']) || !isset($vars['post']) || !Utils::is_uuid($vars['post'])) {
				header("42", true, 400);
				return ;
			}

			$post = Post::query($vars['post']);
			if ($post == null) {
				header("42", true, 404);
				return ;
			}

			// delete any html balise
			$content = preg_replace('/<[^>]*>/', '', $vars['content']);
			//create the comment
			$comment = new Comment(array('author' => $_SESSION['user'], 'post' => $vars['post'], 'content' => $content));
			try {
				$comment->create();
			} catch (Exception $e) {
				header("42", true, 409);
				return ;
			}
			// send email to the author
			Utils::sendMail(Utils::NEW_COMMENT, User::query($post->author), $comment);


			// return success if created
			header("42", true, 201);
			break ;
		}
		default : {
			header("42", true, 400);
		}
	}

?>
