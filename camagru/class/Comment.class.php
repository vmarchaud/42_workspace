<?PHP

require_once 'Utils.class.php';
require_once 'Database.class.php';
require_once 'User.class.php';

class Comment {

	public $id;
	public $post;
	public $author;
	public $state;
	public $content;
	public $date;

	public function __construct ( $kwargs ) {
		// if args null, construct an empty instance for a fetch
		if ($kwargs == null)
			return ;
		// If we got all required field, create the comment
		if (array_key_exists("author", $kwargs) && array_key_exists("content", $kwargs) && array_key_exists("post", $kwargs)) {
			$this->id = Utils::gen_uuid();
			$this->author = $kwargs['author'];
			$this->post = $kwargs['post'];
			$this->content = $kwargs['content'];
			$this->state = "SHOWN";
		}
	}

	// This function is used to insert a new comment into the database from the current instance
	public function create() {
		$db = Database::getInstance();
		$stmt = $db->prepare("INSERT INTO comments (id, post, author, state, content) VALUES (?, ?, ?, ?, ?)");
		$stmt->execute(array($this->id, $this->post, $this->author, $this->state, $this->content));
	}

	// This function is used to query an post from his id and return an comment instance
	public static function query( $id ) {
		$db = Database::getInstance();
		$stmt = $db->prepare("SELECT * FROM comments WHERE id = '$id'");
		$stmt->setFetchMode(PDO::FETCH_INTO, new Comment(null));
		if ($stmt->execute())
			return $stmt->fetch();
		else
			return null;
	}

	// This function is used to query an post from the original post and return an array of post
	public static function fromPost( $id ) {
		$db = Database::getInstance();
		$stmt = $db->prepare("SELECT * FROM comments WHERE post = '$id' ORDER BY date DESC");
		if ($stmt->execute())
			return $stmt->fetchAll(PDO::FETCH_OBJ);
		else
			return null;
	}

	// This function is used to "delete" an comment
	public function delete() {
		$db = Database::getInstance();
		$stmt = $db->prepare("DELETE FROM comments WHERE id = '$this->id'");
		$stmt->execute();
	}
}
?>
