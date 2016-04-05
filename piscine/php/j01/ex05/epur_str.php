#!/usr/bin/php 
<?PHP
	function epur($str)
	{
		$str = trim($str);
		$str = preg_replace('/ +/', ' ', $str);
		return ($str);
	}
	
	if (count($argv) != 2)
		return ;
	echo epur($argv[1]) . "\n";
?>
