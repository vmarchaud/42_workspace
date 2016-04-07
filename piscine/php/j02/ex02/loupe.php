#!/usr/bin/php 
<?PHP
	if ($argc == 1)
		return ;
	$content = file_get_contents($argv[1]);
	
	$content = preg_replace_callback('/title="(.*?)"/', 
		function ($matches) {
		return  'title="' . strtoupper($matches[1]) .'"';  
	}, $content);
	$content = preg_replace_callback('/<a [^>]+.*<\/a>/siU',
		function ($matches) {
			return preg_replace_callback('/>.*</siU', function ($matches) {
				return strtoupper($matches[0]);
			}, $matches[0]);
	}, $content);

	print $content;
?>
