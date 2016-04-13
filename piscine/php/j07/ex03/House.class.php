<?PHP
	class House {

		public function introduce() {
			printf('House %s of %s : "%s"' . PHP_EOL, $this->getHouseName(), $this->getHouseSeat(), $this->getHouseMotto());
		}
	}
?>
