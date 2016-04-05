#!/usr/bin/php 
<?PHP
 while (true) {
	 echo "Entrez un nombre: ";
	 $handle = fopen ("php://stdin","r");
	 $line = fgets($handle);
	 if ($line == FALSE)
		 break ;
	 $nbr = trim($line, "\n\r\0\x0B");
	 if (is_numeric($nbr)) {
		 if ($nbr % 2 == 0) {
			 echo "Le chiffre " . $nbr . " est Pair\n";
		 }
		 else {
			 echo "Le chiffre " . $nbr . " est Impair\n";
		 }
	 }
	 else {
		 echo "'" . $nbr . "'" . " n'est pas un chiffre\n";
	 }
 }
?>
