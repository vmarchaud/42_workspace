<?PHP

class NightsWatch {
		protected $_fighters = array();

		public function recruit($obj) {
			if ($obj instanceof IFighter)
				array_push($this->_fighters, $obj);
		}

		public function fight() {
			foreach($this->_fighters as $key => $recruit) {
				$recruit->fight();
			}
		}
}
?>
