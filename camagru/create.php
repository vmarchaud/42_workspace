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
		   	<div>
				<video class="camera" autoplay="true" id="cameraIn"></video>
				<img id="mask" style="display: none;">
			</div>
			<canvas id="canvas" style="display: none;"></canvas>
			<button id="takeScreen">Take picture</button>
			<img id="cameraOut">
		</div>
	</div>
</body>
</html>
