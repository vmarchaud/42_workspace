<?PHP
	if (file_exists("list.csv")) {
		$content = file_get_contents("list.csv");
		echo $content;
	}
?>
