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
			if (!$pwd || !$mail) {
				header("42", true, 400);
				return ;
			}
			// verify if user is not already logged
			if ($_SESSION['user']) {
				header("Location: index.php");
				return ;
			}
			// get the hashed password to compare it
			$pwd = hash("whirpool", $mail . $pwd);

			// get db instance and make the request
			$db = Database::getInstance();
			$stmt = $db->prepare("SELECT * FROM users WHERE mail=$mail AND pwd=$pwd");

			// if it return an user, loggin else return not found
			if ($stmt->execute()) {
				$user = $stmt->fetch();
				$_SESSION['user'] = $user['id'];
				$_SESSION['user_name'] = $user['name'];
				header("42", true, 200);
			}
			else
				header("42", true, 404);
			break ;
		}
		case "logout" : {
			// if there is an id in his session is logged so unset it
			if ($_SESSION['user']) {
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
			if ($_SESSION['user']) {
				header("42", true, 401);
				return ;
			}
			$mail = $_POST['mail'];
			$name = $_POST['name'];
			$pwd = $_POST['pwd'];

			// Verify validity of params
			if (!$mail || !$name || !$pwd) {
				header("42", true, 400);
				return ;
			}
			// Create the user
			$user = new User(array(mail => $mail, name => $name, password => $pwd));
			try {
				$user->create();
			} catch (Exception $e) {
				header("42", true, 409);
				echo $e->getMessage();
				return ;
			}
			// if everything is ok
			header("42", true, 201);
			break ;
		}
	}
?>
