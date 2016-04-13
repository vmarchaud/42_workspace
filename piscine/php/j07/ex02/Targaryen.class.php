<?PHP
class Targaryen {
	function resistsFire() {
		return false;
	}

	function getBurned() {
		if (!$this->resistsFire())
			return "burns alive";
		else
			return "emerges naked but unharmed";
	}
}
?>
