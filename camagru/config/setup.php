<?php
	require_once '../class/Database.class.php';
	// get the content of setup
	$sql = file_get_contents("setup.sql");
	// get db and execute the query
	$db = Database::getInstance();
	$db->query($sql);
	// redirect
	header("Location: /index.php#login");
?>
