#!/usr/bin/php 
<?PHP
	if ($argc == 1)
		return;
	echo trim(preg_replace("/[ \t]+/", ' ', $argv[1]));
?>
