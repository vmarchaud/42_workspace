<?PHP

	$user = $_GET['login'];
	$passwd = $_GET['passwd'];
	if (strlen($user) == 0 || strlen($passwd) == 0)
		return ;
	require("auth.php");
	session_start();

	
	if (auth($user, $passwd) == true) {
		$_SESSION['loggued_on_user'] = $user;
		echo "OK\n";
	}
	else {
		$_SESSION['loggued_on_user'] = "";
		echo "ERROR\n";
	}
?>
