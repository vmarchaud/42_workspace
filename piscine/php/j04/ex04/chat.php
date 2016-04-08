<html>
	<body>
		<?PHP 
			if (file_exists("../htdocs/private/chat") == TRUE) {
				$fd = fopen("../htdocs/private/chat", "r");
				flock($fd, LOCK_SH);
				$messages = unserialize(file_get_contents("../htdocs/private/chat"));
				foreach($messages as $message) {
					printf("[%s] %s : %s <br>", date("H:s", intval($message['time'])), $message['login'], $message['msg']);
				}
				flock($fd, LOCK_UN);
				fclose($fd);
			}
		?>	
	</body>
</html>
