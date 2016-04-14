<html>
    <head>
        <meta charset="utf-8"/>
        <title>Warhammer</title>
      	<link href='//fonts.googleapis.com/css?family=Lato:300' rel='stylesheet' type='text/css'>
      	<link href='../styles/css/game.css' rel='stylesheet' type='text/css'>
		<script src="https://code.jquery.com/jquery-2.2.3.min.js"   integrity="sha256-a23g1Nt4dtEYOj7bR+vTu7+T8VP13humZFBJNIYoEJo="   crossorigin="anonymous"></script>
		<script src="styles/js/game.js"></script>
    </head>
    <body>
		<table border="1">
			<?php
				$case_id = 0;
				for($y = 0; $y < 100; $y++) {
					echo '<tr id="row' . $y .'">';
					for($i = 0; $i < 150; $i++) {
						echo '<td id="case' . $case_id .'"></td>';
						$case_id++;
					}
					echo "</tr>";
				}
			?>
		</table>
    </body>
</html>
