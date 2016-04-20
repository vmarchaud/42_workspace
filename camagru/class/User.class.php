<?PHP

require_once 'Utils.class.php';
require_once 'Database.class.php';

class User {

	const USER = "USER";
	const ADMIN = "ADMIN";
	const MODERATOR = "MODERATOR";
	const NEED_VALID = "NEED_VALIDATION";
	const FORGET_PWD = "FORGET_PASSWD";
	const REGISTER = "REGISTERED";
	const DELTD = "DELETED";

	public $id;
	public $mail;
	public $name;
	public $password;
	public $role;
	public $state;

	// The constructor should only be used when creating a new account
	public function __construct ( $kwargs ) {
		// If we got all required field, create the user, send mail
		if (array_key_exists("name", $kwargs) && array_key_exists("mail", $kwargs) && array_key_exists("password", $kwargs)) {
			$this->id = Utils::gen_uuid();
			$this->mail = $kwargs['mail'];
			$this->name = $kwargs['name'];
			$this->role = isset($kwargs['role']) ? $kwargs['role'] : USER;
			$this->password = hash("whirlpool", $kwargs['mail'] . $kwargs['password']);
			$this->state = NEED_VALID;
			// Send mail
			Utils::sendMail(Utils::VALID_TYPE, $this);
		}
		else {
			// If there are not all required field, just throw an exception
			throw new Exception("You need required field to construct an new user");
		}
	}

	// This function is used to insert a new user into the database from the current instance
	public function create() {
		$db = Database::getInstance();
		$stmt = $db->prepare("INSERT INTO users (id, mail, name, password, role, state)
			VALUES ($this->id, $this->mail, $this->name, $this->password, $this->role, $this->state)");
		$stmt->execute();
	}

	// This function is used to query an user from his id and return an user instance
	public static function query( $id ) {
		$db = Database::getInstance();
		$stmt = $db->prepare("SELECT * FROM users WHERE uuid = $id");
		$stmt->setFetchMode(PDO::FETCH_INTO, $this);
		if ($stmt->execute())
			return $stmt->fetch();
		else
			return null;
	}

	// This function is used to "delete" an account, the data will still exist but user will not be able to connect
	public function delete() {
		$db = Database::getInstance();
		$stmt = $db->prepare("UPDATE users SET state='DELETED' WHERE id = $this->id");
		$stmt->execute();
	}

	// This function is used to update data of an user
	public static function update() {
		$db = Database::getInstance();
		$stmt = $db->prepare("UPDATE users SET mail=?, name=?, password=?, state=? WHERE id = $this->id");
		$stmt->execute(array($this->mail, $this->name, $this->password, $this->state));
	}
}
?>
