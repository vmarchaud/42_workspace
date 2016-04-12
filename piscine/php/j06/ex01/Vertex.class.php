<?PHP

require_once 'Color.class.php';

class Vertex {

	private $_x = 0.0;
	private $_y = 0.0;
	private $_z = 0.0;
	private $_w = 1.0;
	private $_color;

	static $verbose = false;
	function __toString() {
		return	sprintf("Vertex ( x: %d, y: %d, z: %d, w: %d, %s )", $this->_x, $this->_y, $this->_z, $this->_w, $this->_color);	
	}

	function __construct( $kwargs ) {
		if (isset($kwargs['color']))
			$this->_color = $kwargs['color'];
		else
			$this->_color = new Color( array("rgb" => 0xffffff));
		if (isset($kwargs['x']))
			$this->_x = $kwargs['x'];
		if (isset($kwargs['y']))
			$this->_y = $kwargs['y'];
		if (isset($kwargs['z']))
			$this->_z = $kwargs['z'];
		if (isset($kwargs['w']))
			$this->_w = $kwargs['w'];

		if (Vertex::$verbose)
			echo $this . " constructed\n";
	}

	function __destruct() {
		if (Vertex::$verbose)
			echo $this . " destructed\n";
	}
	
	function __get($random) {
		if (Vertex::$verbose)
			echo "You must use the public getter";
		return "";
	}
	
	function __set($random, $value) {
		if (Vertex::$verbose)
			echo "You must use the public setter";
	}

	function getColor() { return $this->_color; }
	function getX() { return $this->_x; }
	function getY() { return $this->_y; }
	function getZ() { return $this->_z; }
	function getW() { return $this->_w; }

	function setColor($color) { $this->_color = $color; }
	function setX($x) { $this->_x = $x; }
	function setY($y) { $this->_y = $y; }
	function setZ($z) { $this->_z = $z; }
	function setW($w) { $this->_w = $w; }
	

	static function doc() {
		$content = file_get_contents("./Vertex.doc.txt");
		echo $content;
	}
}

?>
