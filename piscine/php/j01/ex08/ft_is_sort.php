<?PHP
	function ft_is_sort($array) {
		$sort = array_merge(array(), $array);
		sort($sort);
		for($i = 0; $i < count($array); $i++) {
			if (strcmp($array[$i], $sort[$i]) != 0)
				return false;
		}
		return true;
	}
?>
