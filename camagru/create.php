<?php
	session_start();

	if (!isset($_SESSION['user'])) {
		header("Location: /index.php#login");
		return ;
	}

	require_once 'header.php';

?>
	<div class="content" >
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
			<button id="takeScreen" disabled="true">Upload</button>
			<img id="cameraOut">
		</div>
		<div class="sidebar">
			<div  id="postsList">
			   <ul></ul>
		   </div>
		</div>
	</div>
	<script type="text/javascript">  onload_create(); </script>

<?php
	require_once 'footer.php';
?>
