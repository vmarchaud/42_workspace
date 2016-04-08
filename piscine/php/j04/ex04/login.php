<?PHP

	$user = $_POST['login'];
	$passwd = $_POST['passwd'];
	if (strlen($user) == 0 || strlen($passwd) == 0)
		return ;
	require("auth.php");
	session_start();
	
	if (auth($user, $passwd) == true) {
		$_SESSION['loggued_on_user'] = $user;
		echo '<iframe name="chat" src="chat.php" width="100%" height="550px">
			</iframe><iframe src="speak.php" width="100%" height="50px"></iframe>';
	}
	else {
		$_SESSION['loggued_on_user'] = "";
		echo "ERROR\n";
	}
?>
