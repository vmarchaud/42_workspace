<?PHP
class Tyrion extends Lannister {

		public function __construct() {
			Lannister::__construct();
			echo "My name is Tyrion" . PHP_EOL;
		}

		public function getSize() {
			return "Short";
		}
	}
?>
