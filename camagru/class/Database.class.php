<?PHP

require '../config/database.php';

class Database {
	static function getInstance() {
		global $DB_DSN, $DB_USER, $DB_PASSWORD;
		try {
			$db = new PDO($DB_DSN, $DB_USER, $DB_PASSWORD);
		    $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
		} catch (PDOException $e) {
			die("DB ERROR: ". $e);
		}
		return $db;
	}
}

?>
