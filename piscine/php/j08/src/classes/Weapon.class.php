<?PHP
 abstract class Weapon {
	
	const NONE = 0;

	const SQUARE = 10;
	const CIRCLE = 11;
	const CONE = 12;
	const LINE = 13;
	
	protected $_charge = 0;
	protected $_distance = array(0, 0, 0);
	protected $_effect = Weapon::NONE;
	protected $_rayon = 0;

    
    public function get_charge() {
        return $this->_charge;
    }
    
    public function set_charge($_charge) {
        $this->_charge = $_charge;
    }
    
    public function get_distance() {
        return $this->_distance;
    }
    
    public function set_distance($_distance) {
        $this->_distance = $_distance;
    }
    
    public function get_effect() {
        return $this->_effect;
    }
    
    public function set_effect($_effect) {
        $this->_effect = $_effect;
    }
    
    public function get_rayon() {
        return $this->_rayon;
    }
    
    public function set_rayon($_rayon) {
        $this->_rayon = $_rayon;
	}

	function __get($attrb) {
		return "";
	}

	function __set($attrb, $value) {
		return ;
	}

	static function doc() {
		return file_get_contents("docs/Weapon.doc.txt");
	}	
}
?>
