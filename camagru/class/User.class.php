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
		// if args null, construct an empty instance for a fetch
		if ($kwargs == null)
			return ;
		// If we got all required field, create the user, send mail
		if (array_key_exists("name", $kwargs) && array_key_exists("mail", $kwargs) && array_key_exists("password", $kwargs)) {
			$this->id = Utils::gen_uuid();
			$this->mail = $kwargs['mail'];
			$this->name = $kwargs['name'];
			$this->role = isset($kwargs['role']) ? $kwargs['role'] : User::USER;
			$this->password = hash("whirlpool", $kwargs['mail'] . $kwargs['password']);
			$this->state = User::NEED_VALID;
			// Send mail
			Utils::sendMail(Utils::VALID_TYPE, $this);
		}
	}

	// This function is used to insert a new user into the database from the current instance
	public function create() {
		$db = Database::getInstance();
		$stmt = $db->prepare("INSERT INTO users (id, mail, name, password, role, state) VALUES (?, ?, ?, ?, ?, ?)");
		$stmt->execute(array($this->id, $this->mail, $this->name, $this->password, $this->role, $this->state));
	}

	// This function is used to query an user from his id and return an user instance
	public static function query( $id ) {
		$db = Database::getInstance();
		$stmt = $db->prepare("SELECT * FROM users WHERE id = ?");
		$stmt->setFetchMode(PDO::FETCH_INTO, new User(null));
		if ($stmt->execute(array($id)))
			return $stmt->fetch();
		else
			return null;
	}

	// This function is used to "delete" an account, the data will still exist but user will not be able to connect
	public function delete() {
		$db = Database::getInstance();
		$stmt = $db->prepare("UPDATE users SET state='DELETED' WHERE id = ?");
		$stmt->execute(array($this->id));
	}

	// This function is used to update data of an user
	public function update() {
		$db = Database::getInstance();
		$stmt = $db->prepare("UPDATE users SET mail=?, name=?, password=?, state=? WHERE id = ?");
		$stmt->execute(array($this->mail, $this->name, $this->password, $this->state, $this->id));
	}
}
?>
