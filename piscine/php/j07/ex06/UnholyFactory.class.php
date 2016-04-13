<?PHP 

	class UnholyFactory {


		private $_types = array();

		public function absorb($obj) {
			if ($obj instanceof Fighter) {
				if (isset($this->_types[$obj->getType()]) == false) {
					printf("(Factory absorbed a fighter of type %s)\n", $obj->getType());
					$this->_types[$obj->getType()] = $obj;
				}
				else {
					printf("(Factory already absorbed a fighter of type %s)\n", $obj->getType());
				}
			}
			else {
				printf("(Factory can't absorb this, it's not a fighter)\n");
			}
		}

		public function fabricate($type) {
			if (isset($this->_types[$type])) {
				printf("(Factory fabricates a fighter of type %s)\n", $type);
				return $this->_types[$type];
			}
			else {
				printf("(Factory hasn't absorbed any fighter of type %s)\n", $type);
			}
		}
	}
?>
