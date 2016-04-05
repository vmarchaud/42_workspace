#!/usr/bin/php 
<?PHP
	if (count($argv) != 4)
	{
		echo "Invalid Paramenters\n";
		return ;
	}

	$first = trim($argv[1]);
	$second = trim($argv[2]);
	$third = trim($argv[3]);

	if ($second == '+')
		echo $first + $third;
	else if ($second == '-')
		echo $first - $third;
	else if ($second == '*')
		echo $first * $third;
	else if ($second == '/')
		echo $first / $third;
	else if ($second == '%')
		echo $first % $third;
	echo "\n";
?>
