<?php

abstract class SpaceShip {

	const ENABLED_ORDER = 0;
	const ENABLED_MOVE = 1;
	const ENABLED_SHOOT = 2;
	const DISABLED = 3;
	const DEAD = 4;
	const NONE = 5;
	
    protected $_name = "Default Ship";
    protected $_sprite = null;
    protected $_size = new array (1,1);
    protected $_resistance = 0;
    protected $_power = 0;
    protected $_speed = 0;
    protected $_weight = 0;
	protected $_shield = 0;
	protected $_state = ShapeShip::NONE;
    protected $_weapons = array();
	protected $_bonus = array();
	protected $_position = array(0,0);

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
