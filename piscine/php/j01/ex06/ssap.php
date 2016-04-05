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

	sort($out, SORT_STRING);
	for($i = 0; $i < count($out); $i++) {
		echo $out[$i] . "\n";
	}

?>
