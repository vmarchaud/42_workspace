#!/usr/bin/php 
<?PHP

	function mystrlen($str) {
		$i = 0;
	 	$tab = str_split($str);	
		foreach($tab as $value)
			$i++;
		return $i;
	}

	$input = $argv[1];
	$tab = explode(' ', $input);
	if (count($tab) != "5")
	{	
		echo "Wrong Format\n";
		return ;
	}

	$dayAvailable = array("lundi", "mardi", "mercredi", "jeudi", "vendredi", "samedi", "dimanche");
	$monthAvailable = array("janvier", "fevrier", "mars", "avril", "mai", "juin", "juillet", "aout", "septembre", "octobre", "novembre", "decembre");

	if (in_array(strtolower($tab[0]), $dayAvailable) == FALSE) {
		echo "Wrong Format\n"; return ;
	}
	if (is_numeric($tab[1]) == FALSE || $tab[1] > 31 || $tab[1] < 0) {
		echo "Wrong Format\n"; return ;
	}
	if (in_array(strtolower($tab[2]), $monthAvailable) == FALSE) {
		echo "Wrong Format\n"; return ;
	}
	if (is_numeric($tab[3]) == FALSE || mystrlen($tab[3]) != 4) {
		echo "Wrong Format\n"; return ;
	}	
	if (preg_match("/([01]?[0-9]|2[0-3]):[0-5][0-9](:[0-5][0-9])/", $tab[4]) == FALSE) {
		echo "Wrong Format\n"; return ; 
	}
	date_default_timezone_set("Europe/Paris");

	$index = array_search(strtolower($tab[2]), $monthAvailable) + 1;
	if ($index < 10)
		$index = "0" . $index;

echo strtotime($tab[3] .":" . $index  . ":" . $tab[1] . " " . $tab[4]) . "\n";

?>
