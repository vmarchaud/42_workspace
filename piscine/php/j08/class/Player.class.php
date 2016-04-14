<?PHP

class Player {
	protected $_ships = array ();
	protected $_turn = false;

	public function addship($ship) {
		array_push($this->_ships, $ship);
	}
}
?>
