<?PHP 
	
    $user = $_POST['login'];
    $passwd = $_POST['passwd'];
    $salty = "saltyboy";
    
   	if ($_POST['submit'] != "OK") {
		echo "ERROR\n";
		return ;
	}
	
    if ($user && $passwd && strlen($user) > 0 && strlen($passwd) > 0) {
        if (file_exists("../htdocs/private/passwd") == TRUE)
            $accounts = unserialize(file_get_contents("../htdocs/private/passwd"));
		else {
			if (file_exists("../htdocs/") == false)
				mkdir("../htdocs");
			if (file_exists("../htdocs/private/") == false)
				mkdir("../htdocs/private/");
            $accounts = array();
		}
        foreach($accounts as $account) {
            if ($account['login'] == $user) {
                echo "ERROR\n";
                return ;
            }
        }
        $accounts = array_merge($accounts, array(array("login" => $user, "passwd" => hash("sha256", $salty . $user . $passwd))));
        file_put_contents("../htdocs/private/passwd", serialize($accounts));
		header("Location: index.html");	
		echo "OK\n";
	}
    else {
        echo "ERROR\n";
    }
?>
