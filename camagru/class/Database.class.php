<?PHP

require_once '../config/database.php';
echo($DB_DSN);

class Database {

	static function getInstance() {
		$db = null;
		echo($DB_DSN);
		echo($DB_USER);
		echo($DB_PASSWORD);
		
		try {
			$db = new PDO($DB_DSN, $DB_USER, $DB_PASSWORD);
		    $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
		} catch (PDOException $e) {
			print_r("DB ERROR: ". $e);
		}
		return $db;
	}
}
?>
