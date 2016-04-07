<?PHP
	if ($_SERVER['PHP_AUTH_USER'] == "zaz" && $_SERVER['PHP_AUTH_PW'] == "jaimelespetitsponeys") {
		echo "<html><body>\nBonjour Zaz<br />\n";
		echo "<img src='data:image/png;base64," . base64_encode(file_get_contents("../img/42.png")) . "'>\n";
		echo "</body></html>\n";
	}
	else {
		header("HTTP/1.0 401 Unauthorized");
		header("WWW-Authenticate: Basic realm=''Espace membres''");
		header("Content-Type: text/html");
		echo "<html><body>Cette zone est accessible uniquement aux membres du site</body></html>\n";
	}
?>
