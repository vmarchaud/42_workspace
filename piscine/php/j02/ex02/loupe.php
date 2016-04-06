#!/usr/bin/php 
<?PHP
	if ($argc == 1)
		return ;
	$content = file_get_contents($argv[1]);
	
	$content = preg_replace_callback('/<a(.*?)title="(.*?)"/', 
	function ($matches) {
		return  '<a' . $matches[1] . 'title="' . strtoupper($matches[2]) .'"';  
	}, $content);
	$content = preg_replace_callback('/<a(.*?)>(.*?)</',
	function ($matches) {
			return  '<a' . $matches[1] . '>' . strtoupper($matches[2]) .'<';
	}, $content);

	print $content;
?>
