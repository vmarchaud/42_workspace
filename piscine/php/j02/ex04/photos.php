#!/usr/bin/php 
<?PHP
	function get_data_from_url($url) {
		$ch = curl_init();
		curl_setopt($ch, CURLOPT_URL, $url);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
		$data = curl_exec($ch);
		curl_close($ch);
		return $data;
	}
	
	$content = get_data_from_url($argv[1]);
	$images = array();
	$target = preg_replace('((https?)\:\/\/)?', '', $argv[1]);
	$target = explode('/', $target)[0];
	mkdir($target);
	preg_match_all('/<img(.*?)src="(.*?)"/', $content, $images);
	foreach($images[2] as $url) {
		$image = get_data_from_url($url);
		$name = explode('/', $url);
		$name = $name[count($name) - 1];
		file_put_contents("./" . $target . "/" . $name, $image);
	}
?>
