#!/usr/bin/php 
<?PHP
	if (count($argv) != 2)
	{
		echo "Invalid Paramenters\n";
		return ;
	}
	
	$line = trim(preg_replace('/ +/', '', $argv[1]));


	if (strpos($line, '+') !== FALSE) {
		$values = explode('+', $line);
		if (count($values) != 2 || !is_numeric($values[0]) || !is_numeric($values[1])) {
			echo "Syntax Error\n";
			return ;
		}
		echo $values[0] + $values[1];
	}
	else if (strpos($line, '-') !== FALSE) {
		$values = explode('-', $line);
		if (count($values) != 2 || !is_numeric($values[0]) || !is_numeric($values[1])) {
			echo "Syntax Error\n";
			return ;
		}
		echo $values[0] - $values[1];
	}

	else if (strpos($line, '*') !== FALSE) {
		$values = explode('*', $line);
		if (count($values) != 2 || !is_numeric($values[0]) || !is_numeric($values[1])) {
			echo "Syntax Error\n";
			return ;
		}
		echo $values[0] * $values[1];
	}

	else if (strpos($line, '/') !== FALSE) {
		$values = explode('/', $line);
		if (count($values) != 2 || !is_numeric($values[0]) || !is_numeric($values[1])) {
			echo "Syntax Error\n";
			return ;
		}
		echo $values[0] / $values[1];
	}

	else if (strpos($line, '%') !== FALSE) {
		$values = explode('%', $line);
		if (count($values) != 2 || !is_numeric($values[0]) || !is_numeric($values[1])) {
			echo "Syntax Error\n";
			return ;
		}
		echo $values[0] % $values[1];
	}
	else
		echo "Syntax Error\n";

	echo "\n";
?>
