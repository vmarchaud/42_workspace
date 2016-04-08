<?PHP 
	
    $user = $_POST['login'];
    $passwd = $_POST['passwd'];
    $salty = "saltyboy";
    
    
    
    if ($user && $passwd && strlen($user) > 0 && strlen($passwd) > 0) {
        if (file_exists("/private/") == TRUE)
            $accounts = unserialize(file_get_contents("./passwd"));
        else
            $accounts = array();
        
        foreach($accounts as $account) {
            if ($account['login'] == $user) {
                echo "ERROR\n";
                return ;
            }
        }
        $accounts = array_merge($accounts, array("login" => $user, "passwd" => hash("sha256", $salty . $user . $passwd)));
        file_put_contents("./passwd", serialize($accounts));
        echo "OK\n";
    }
    else {
        echo "ERROR\n";
    }
?>