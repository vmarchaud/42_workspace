<?PHP

require_once '../config/database.php';

class Database {
	public $db = null;

	static function getInstance() {
		if (!is_null($this->db))
			return $this->db;
		try {
			$this->db = new PDO($DB_DSN, $DB_USER, $DB_PASSWORD);
		    $this->db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
		} catch (PDOException $e) {
			die("DB ERROR: ". $e->getMessage());
		}
		return $this->db;
	}
}
?>
