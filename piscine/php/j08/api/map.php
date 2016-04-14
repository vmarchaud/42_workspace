<?PHP
	session_start();
	require_once '../class/Game.class.php';
	header("Content-Type: application/json");
	
	if ($_SESSION['party_id']) {
		$party = Game::load($_SESSION['party_id']);
		$ships = array();
		foreach ($party->getPlayers() as $player) {
			foreach ($player->getShips() as $ship) {
				$new = array();
				$new['owner'] = $player->getColor();
				$new['size'] = $ship->getSize();
				$new['position'] = $ship->getPosition();
				$new['name'] = $ship->getName();
				$new['sprite'] = "styles/img/sprites/" . $ship->getSprite();
				array_push($ships, $new);
			}
		}
		echo json_encode($ships);
		header("HTTP/1.0 200 OK");
	}
	else {
		header("HTTP/1.0 401 Unauthorized");
	}
?>