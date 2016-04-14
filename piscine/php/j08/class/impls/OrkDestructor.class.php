<?PHP
	require_once '../Weapon.class.php';
	require_once '../SpaceShip.class.php';

	class OrkDestructor extends SpaceShip {
	
		function __construct () {
			$this->_name = "Ork Destructor";
			$this->_size_x = 2;
			$this->_size_y = 1;
			$this->_power = 10;
			$this->_resistance = 4;
			$this->_weight = 3;
			$this->_speed = 19;
			$this->_weapons = array( new MultipleLaser() );
		}	
	}
?>
