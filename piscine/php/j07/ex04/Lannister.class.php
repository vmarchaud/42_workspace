<?PHP 
class Lannister {

	function sleepWith($obj) {
		if ($obj instanceof Stark) {
			echo "Let's do this" . PHP_EOL;
		}
		else if ($obj instanceof Lannister) {
			echo "Not even if I'm drunk !" . PHP_EOL;
		}
	}

}
?>
