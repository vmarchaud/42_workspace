<?PHP

require_once 'Color.class.php';

class Vertex {

	private $_x = 0.0;
	private $_y = 0.0;
	private $_z = 0.0;
	private $_w = 0.0;
	private $_color;

	static $verbose = false;

	function __construct( $kwargs ) {
		if (isset($kwargs['color']))
			$this->color = $kwargs['color'];
		else
			$this->color = new Color( array(rgb => 0xffffff));
		if (isset($kwargs['x']))
			$this->x = $kwargs['x'];
		if (isset($kwargs['y']))
			$this->y = $kwargs['y'];
		if (isset($kwargs['z']))
			$this->z = $kwargs['z'];
		if (Vertex::verbose)

	}


}

?>
