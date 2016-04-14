<?PHP

class Player {
	protected $_ships = array ();
	protected $_color = "red";

	public function addShip($ship) {
		array_push($this->_ships, $ship);
	}
	
	public function getShips() {
		return $this->_ships;
	}
	
	public function getColor() {
		return $this->_color;
	}
}
?>
