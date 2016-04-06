#!/usr/bin/php 
<?PHP	
	$fd = fopen("/var/run/utmpx", "r");
	$users = array();
	while ($line = fread($fd, 628)) {
		$line = unpack("a256user/a4id/a32line/ipid/itype/I2time", $line);
		if (strcmp($line['type'], "7") == 0)
			array_push($users, $line);
	}
	date_default_timezone_set("Europe/Paris");
	foreach($users as $user) {
		printf("%s %s %s\n", $user['user'], $user['line'], date("M j H:i", $user['time1']));
	}
?>
