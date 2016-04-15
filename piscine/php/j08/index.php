<?PHP
	require_once './class/Game.class.php';
	session_start();
	if (count($_SESSION) == 0) {
		$game = new Game();
		$_SESSION['party_id'] = $game->getId();
		$game->save();
	} else {
		header('Location: game.php');
	}
?>
