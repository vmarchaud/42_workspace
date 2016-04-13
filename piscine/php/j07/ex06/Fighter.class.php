<?PHP
	class Fighter {
		
		protected $_type;

		public function __construct($type) {
			$this->_type = $type;
        }

        public function getType() {
            return $this->_type;
        }
	}
?>
