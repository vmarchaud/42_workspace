<?PHP 
class Jaime extends Lannister{
	
	function sleepWith($obj) {
		if ($obj instanceof Cersei) {
			echo "With pleasure, but only in a tower in Winterfell, then." . PHP_EOL;
		}
		else
			parent::sleepWith($obj);
	}

}
?>
