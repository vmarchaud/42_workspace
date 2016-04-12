<?PHP

class Color {
	
	private $_red = 0;
	private $_green = 0;
	private $_blue = 0;
	
	public static $verbose = false;

	function __construct( $kwargs ) {
		if (isset($kwargs['rgb'])) {
			$number = intval($kwargs['rgb']);
			$this->_blue = 	$number & 0xff;
			$this->_green = $number >> 8 & 0xff;
			$this->_red = ($number >> 16) & 0xff;
		}
		else {
			if (isset($kwargs['red']))
				$this->_red = intval($kwargs['red']);
			if (isset($kwargs['blue']))
				$this->_blue = intval($kwargs['blue']);
			if (isset($kwargs['green']))
				$this->_green = intval($kwargs['green']);
		}
		if (Color::$verbose)
			printf("Color( red: %3d, green: %3d, blue: %3d ) constructed.\n", $this->_red, $this->_green, $this->_blue);
	}

	function __destruct() {
		if (Color::$verbose)
			printf("Color( red: %3d, green: %3d, blue: %3d ) destructed.\n", $this->_red, $this->_green, $this->_blue);
	}

	function __toString() {
		return sprintf("Color( red: %3d, green: %3d, blue: %3d )", $this->_red, $this->_green, $this->_blue);
	}

	static function doc() {
		$content = file_get_contents("./Color.doc.txt");
		echo $content;
	}

	function add($color) {
		$red = $color->_red + $this->_red;
		if ($red > 255)
			$red = 255;
		else if ($red < 0)
			$red = 0;
		$blue = $color->_blue + $this->_blue;
		if ($blue > 255)
			$blue = 255;
		else if ($blue < 0)
			$blue = 0;
		$green = $color->_green + $this->_green;
		if ($green > 255)
			$green = 255;
		else if ($green < 0)
			$green = 0;
		return new Color(array("red" => $red, "blue" => $blue, "green" => $green));
	}
	
	function mult($factor) {
		$red = $factor * $this->_red;
		if ($red > 255)
			$red = 255;
		else if ($red < 0)
			$red = 0;
		$blue = $factor * $this->_blue;
		if ($blue > 255)
			$blue = 255;
		else if ($blue < 0)
			$blue = 0;
		$green = $factor * $this->_green;
		if ($green > 255)
			$green = 255;
		else if ($green < 0)
			$green = 0;
		return new Color(array("red" => $red, "blue" => $blue, "green" => $green));
	}

	function sub($color) {
		$red = $this->_red - $color->_red;
		if ($red > 255)
			$red = 255;
		else if ($red < 0)
			$red = 0;
		$blue = $this->_blue - $color->_blue;
		if ($blue > 255)
			$blue = 255;
		else if ($blue < 0)
			$blue = 0;
		$green = $this->_green - $color->_green;
		if ($green > 255)
			$green = 255;
		else if ($green < 0)
			$green = 0;
		return new Color(array("red" => $red, "blue" => $blue, "green" => $green));
	}

}
?>
