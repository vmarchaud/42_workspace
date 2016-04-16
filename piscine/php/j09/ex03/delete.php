<?PHP
	$todo = $_POST['todo'];
	if (!$todo)
		return ;
	$content = file_get_contents("list.csv");
	$content = preg_replace("/([0-9]+):" . $todo . "\n/", "", $content);
	file_put_contents("list.csv", $content);
?>
