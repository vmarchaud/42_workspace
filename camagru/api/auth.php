<?PHP
	if (!$_GET['action']) {
		header("42", true, 400);
		return ;
	}
	session_start();
	require_once '../class/Database.class.php';
	require_once '../class/User.class.php';

	switch($_GET['action']) {
		case "login" : {
			// get post informations
			$mail = $_POST['mail'];
			$pwd = $_POST['pwd'];

			// verify if there are correct
			if (!$pwd || !$mail || !filter_var($mail, FILTER_VALIDATE_EMAIL)) {
				header("42", true, 400);
				return ;
			}
			// verify if user is not already logged
			if (isset($_SESSION['user'])) {
				header("Location: /index.php", true, 200);
				return ;
			}
			// get the hashed password to compare it
			$pwd = hash('whirlpool', $mail . $pwd);

			// get db instance and make the request
			$db = Database::getInstance();
			$stmt = $db->prepare("SELECT * FROM users WHERE mail=? AND password=?");
			$stmt->setFetchMode(PDO::FETCH_INTO, new User(null));
			$stmt->execute(array($mail, $pwd));

			// if it return an user, loggin else return not found
			if ($stmt->rowCount() == 1) {
				$user = $stmt->fetch();
				if ($user->state === User::NEED_VALID || $user->state === User::DELTD) {
					header("42", true, 403);
					return ;
				}
				$_SESSION['user'] = $user->id;
				$_SESSION['user_name'] = $user->name;
				header("42", true, 200);
			}
			else
				header("42", true, 404);
			break ;
		}
		case "logout" : {
			// if there is an id in his session is logged so unset it
			if (isset($_SESSION['user']) || strlen($_SESSION['user']) == 0) {
				unset($_SESSION['user']);
				unset($_SESSION['user_name']);
				header("42", true, 200);
			}
			// else just sent him bad request cause is not logged
			else
				header("42", true, 401);
			break ;
		}
		case "register" : {
			// Already logged
			if (isset($_SESSION["user"])) {
				header("42", true, 401);
				return ;
			}
			$mail = $_POST['mail'];
			$name = $_POST['name'];
			$pwd = $_POST['pwd'];

			// Verify validity of params
			if (!$mail || !$name || !$pwd || !filter_var($mail, FILTER_VALIDATE_EMAIL)) {
				header("42", true, 400);
				return ;
			}

			// verify that the mail isnt already used
			$db = Database::getInstance();
			$stmt = $db->prepare("SELECT * FROM users WHERE mail=?");
			$stmt->execute(array($mail));
			if ($stmt->rowCount() > 0) {
				header("42", true, 409);
				return ;
			}

			// get out of any html balise
			$name = preg_replace('/<[^>]*>/', '', $name);

			// Create the user
			$user = new User(array('mail' => $mail, 'name' => $name, 'password' => $pwd));
			try {
				$user->create();
			} catch (Exception $e) {
				header("42", true, 500);
				return ;
			}
			// if everything is ok
			header("42", true, 201);
			break ;
		}
		default : {
			header("42", true, 400);
		}
	}
?>
