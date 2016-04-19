<?PHP 
	session_start();
	if ($_SESSION['id'])
		header("Location: public/index.html");
	else
		header("Location: public/login.html");
?>
