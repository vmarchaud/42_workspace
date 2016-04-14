<?PHP
	require_once '../Weapon.class.php';
	require_once '../SpaceShip.class.php';

	class ImperialDestroyer extends SpaceShip {
	
		function __construct () {
			$this->_name = "Imperial Destroyer";
			$this->_size_x = 3;
			$this->_size_y = 1;
			$this->_power = 10;
			$this->_resistance = 4;
			$this->_weight = 4;
			$this->_speed = 18;
			$this->_weapons = array( new MultipleLaser() );
		}	
	}
?>
