<?PHP
	function auth($login, $password) {
		if (strlen($login) == 0 || strlen($password) == 0)
			return false ;
		$accounts = unserialize(file_get_contents("../htdocs/private/passwd"));
		foreach($accounts as $account) {
			if ($account['login'] == $login && $account['passwd'] == hash("sha256", "saltyboy" . $login . $password))
				return true;
		}
		return false;
	}
?>
