<?PHP 

class Database {
	private $_url = "status.hardfight.fr";
	private $_user = "root";
	private $_pwd = "yolo42";
	private $_db_name = "camagru";
	
	public $db = null;

	static function getInstance() {
		if (!is_null($this->db))
			return $this->db;
		try {
			$this->db = new PDO("mysql:host=$_url;dbname=$_db_name", $_user, $_pwd);
		    $this->db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);	
		} catch (PDOException $e) {
			die("DB ERROR: ". $e->getMessage());
		}
		return $this->db;
	}
}
?>
