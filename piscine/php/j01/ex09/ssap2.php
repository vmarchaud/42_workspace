#!/usr/bin/php 
<?PHP
	$out = array();
	for($i = 1; $i < count($argv); $i++) {
		if (strpos($argv[$i], ' ') !== FALSE) {
			$tmp = explode(' ', $argv[$i]);
			$out = array_merge($out, $tmp);
		}
		else {
			array_push($out, $argv[$i]);
		}
	}

	$alpha = array();
	$number = array();
	$other = array();

	for($i = 0; $i < count($out); $i++) {
		if (is_numeric($out[$i]))
			array_push($number, $out[$i]);
		else if (ctype_alpha($out[$i]))
			array_push($alpha, $out[$i]);
		else
			array_push($other, $out[$i]);
	}
	natcasesort($alpha);
	sort($number, SORT_STRING);
	natcasesort($other);
	
	foreach ($alpha as $value) {
		    echo $value  . "\n";
	}

	foreach ($number as $value) {
		    echo $value  . "\n";
	}

	foreach ($other as $value) {
		    echo $value  . "\n";
	}

?>
