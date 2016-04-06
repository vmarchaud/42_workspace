<?PHP
	function ft_split($str)
	{
		$str = preg_replace("/ +/", ' ', $str);
		return (explode(' ', $str));
	}
?>
