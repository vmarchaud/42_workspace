<?PHP 
	$todo = $_POST['todo'];
if ($todo) {
		if (file_exists("list.csv"))
			$content = file_get_contents("list.csv");
		else
			$content = "";
		$content = $content . rand() .";" . $todo . "\n";
		file_put_contents("list.csv", $content);
	}
?>
