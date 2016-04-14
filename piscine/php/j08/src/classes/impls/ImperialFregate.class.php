<?PHP
	require_once '../Weapon.class.php';
	require_once '../SpaceShip.class.php';

	class ImperialFregate extends SpaceShip {
	
		function __construct () {
			$this->_name = "Imperial Fregate";
			$this->_size_x = 4;
			$this->_size_y = 1;
			$this->_power = 10;
			$this->_resistance = 5;
			$this->_weight = 4;
			$this->_speed = 15;
			$this->_weapons = array( new MultipleLaser() );
		}	
	}
?>
