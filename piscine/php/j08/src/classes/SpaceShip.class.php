<?php

abstract class SpaceShip {

	const ENABLED_ORDER = 0;
	const ENABLED_MOVE = 1;
	const ENABLED_SHOOT = 2;
	const DISABLED = 3;
	const DEAD = 4;
	const NONE = 5;
	
    protected $_name = "Default Ship";
    protected $_size_x = 1;
    protected $_size_y = 1;
    protected $_resistance = 0;
    protected $_power = 0;
    protected $_speed = 0;
    protected $_weight = 0;
	protected $_shield = 0;
	protected $_state = ShapeShip::NONE;
    protected $_weapons = array();
    protected $_bonus = array();

	public function set_bonus($_bonus) {
        $this->_bonus = $_bonus;
    }
    
    public function get_bonus() {
        return $this->_bonus;
    }
    
    public function set_weapons($_weapons) {
        $this->_weapons = $_weapons;
    }
    
    public function get_weapons() {
        return $this->_weapons;
    }
    
    public function set_state($_state) {
        $this->_state = $_state;
    }
    
    public function get_state() {
        return $this->_state;
    }
    
    public function set_shield($_shield) {
        $this->_shield = $_shield;
    }
    
    public function get_shield() {
        return $this->_shield;
    }
    
    public function set_weight($_weight) {
        $this->_weight = $_weight;
    }
    
    public function get_weight() {
        return $this->_weight;
    }
    
    public function set_speed($_speed) {
        $this->_speed = $_speed;
    }
    
    public function get_speed() {
        return $this->_speed;
    }
    
    public function set_power($_power) {
        $this->_power = $_power;
    }
    
    public function get_power() {
        return $this->_power;
    }
    
    public function set_resistance($_resistance) {
        $this->_resistance = $_resistance;
    }
    
    public function get_resistance() {
        return $this->_resistance;
    }
    
    public function set_size_y($_size_y) {
        $this->_size_y = $_size_y;
    }
    
    public function get_size_y() {
        return $this->_size_y;
    }
    
    public function set_size_x($_size_x) {
        $this->_size_x = $_size_x;
    }
    
    public function get_size_x() {
        return $this->_size_x;
    }
    
    public function set_name($_name) {
        $this->_name = $_name;
    }
    
    public function get_name() {
        return $this->_name;
	}

	function __get($attrb) {
		return "";
	}

	function __set($attrb, $value) {
		return ;
	}

	static function doc() {
		return file_get_contents("docs/SpaceShip.doc.txt");
	}	
}
?>
