#!/usr/bin/php 
<?PHP
	if ($argc < 3)
		return ;
	$keyword = $argv[1]; 
	for ($i = $argc - 1; $i >= 2; $i--) {
		if (strpos($argv[$i], ':') === FALSE) {
			echo "Syntax Error\n";
			return ;
		}
		$values = explode(':', $argv[$i]);
		if (count($values) < 2) {
			echo "Syntax Error\n";
			return ;
		}
		if (strcmp($keyword, $values[0]) == 0) {
			echo $values[1] . "\n";
			return ;
		}
	}

?>
