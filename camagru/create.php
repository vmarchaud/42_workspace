<?php
	require_once 'header.php';

	if (!isset($_SESSION['user'])) {
		header("Location: /index.php#login");
		return ;
	}
?>
	<div class="content">
		<div class="capture">
			<div id="maskList">
			   <ul></ul>
		   </div>
		   	<center style="position: relative;">
				<video class="camera" id="cameraIn"></video>
				<img id="mask" style="display: none;">
			</center>
			<input id="fileinput" type="file" name="pic" accept="image/*" style="display: none;">
			<canvas id="canvas" style="display: none;"></canvas>
			<button id="takeScreen">Upload</button>
			<img id="cameraOut">
		</div>
	</div>
	<div class="sidebar">
	</div>
</body>
</html>
