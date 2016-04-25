<?PHP

require_once 'Utils.class.php';
require_once 'Database.class.php';
require_once 'User.class.php';

class Post {

	public $id;
	public $author;
	public $liike;
	public $img;

	// The constructor should only be used when creating a new post
	public function __construct ( $kwargs ) {
		// if args null, construct an empty instance for a fetch
		if ($kwargs == null)
			return ;
		// If we got all required field, create the post
		if (array_key_exists("author", $kwargs) && array_key_exists("img", $kwargs) ) {
			$this->id = Utils::gen_uuid();
			$this->author = $kwargs['author'];
			$this->liike = 0;
			$this->img = $kwargs['img'];
		}
	}

	// This function is used to insert a new post into the database from the current instance
	public function create() {
		$db = Database::getInstance();
		$stmt = $db->prepare("INSERT INTO posts (id, author, liike, img) VALUES (?, ?, ?, ?)");
		$stmt->execute(array($this->id, $this->author, $this->liike, $this->img));
	}

	// This function is used to query an post from his id and return an post instance
	public static function query( $id ) {
		$db = Database::getInstance();
		$stmt = $db->prepare("SELECT * FROM posts WHERE id = '$id'");
		$stmt->setFetchMode(PDO::FETCH_INTO, new Post(null));
		if ($stmt->execute())
			return $stmt->fetch();
		else
			return null;
	}

	// This function is used to query an post from his author and return an array
	public static function fromAuthor( $id ) {
		$db = Database::getInstance();
		$stmt = $db->prepare("SELECT * FROM posts WHERE author = '$id' ORDER BY date ASC");
		if ($stmt->execute())
			return $stmt->fetchAll(PDO::FETCH_OBJ);
		else
			return array();
	}

	// This function is used to "delete" an post
	public function delete() {
		$db = Database::getInstance();
		$stmt = $db->prepare("DELETE FROM posts WHERE id = '$this->id'");
		$stmt->execute();
	}

	// This function is used to update data of an post
	public function update() {
		$db = Database::getInstance();
		$stmt = $db->prepare("UPDATE posts SET liike=? WHERE id = '$this->id'");
		$stmt->execute(array($this->liike));
	}
}
?>
