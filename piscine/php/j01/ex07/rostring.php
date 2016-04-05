#!/usr/bin/php 
<?PHP
	if (count($argv) < 2)
		return ;
	$argv[1] = trim(preg_replace('/ +/', ' ', $argv[1]));
	$out = explode(' ', $argv[1]);
	$tmp = $out[0];
	unset($out[0]);
	array_push($out, $tmp);
	$out = array_values($out);
	for ($i = 0; $i < count($out); $i++) {
		echo trim($out[$i]) . " ";
	}
	echo "\n";
?>
