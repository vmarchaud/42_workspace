<?PHP
	$action = $_GET['action'];
	$name = $_GET['name'];
	$value = $_GET['value'];

	if (!$action || !$name)
		return ;
	if ($action == "get")
		echo $_COOKIE[$name];
	else if ($action == "del")
		setcookie($name, "", time() - 3600);
	else if ($action == "set") {
		setcookie($name, $value, time() + 2592000);
	}
?>
