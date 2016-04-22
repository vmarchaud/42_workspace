<?PHP
class Utils {
	const VALID_TYPE = 0;
	const FORGOT_TYPE = 1;

	// Function used to generate a pseudo random id (type uuid)
	public static function gen_uuid() {
		return sprintf('%04x%04x-%04x-%04x-%04x-%04x%04x%04x',
			mt_rand(0, 0xffff), mt_rand(0, 0xffff), mt_rand(0, 0xffff),
			mt_rand(0, 0x0fff) | 0x4000, mt_rand(0, 0x3fff) | 0x8000,
			mt_rand(0, 0xffff), mt_rand(0, 0xffff), mt_rand(0, 0xffff));
	}

	// Function used to verify that an string is a valid uuid
	public static function is_uuid( $uuid ) {
		if (!is_string($uuid) || (preg_match('/^[0-9a-f]{8}-[0-9a-f]{4}-4[0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$/', $uuid) !== 1) || strlen($uuid) != 36)
		    return false;
		else
			return true;
	}

	// Function is used to generate a random string of X length
	public static function random_string( $length ) {
    	$chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    	return substr(str_shuffle($chars), 0, $length);
	}

	// function used to send a mail to an user
	public static function sendMail($type, $user, $other = null) {
		switch($type) {
			case Utils::VALID_TYPE : {
				// generate a token and save it
				$token = Utils::gen_uuid();
				$db = Database::getInstance();
				$stmt = $db->prepare("INSERT INTO tokens (id, user, type) VALUES (?, ?, ?)");
				$stmt->execute(array($token, $user->id, "REGISTER"));

				// get template and replace variable
				$content = file_get_contents('./mail_template/register.html');
				$content = preg_replace("/%name%/", $user->name, $content);
				$content = preg_replace("/%url%/", "http://" . $_SERVER['HTTP_HOST'] . "/api/mail.php?type=valid&code=" . $token, $content);
				// send mail
				mail($user->mail, "[Instagrume] Valid your account to use our site !", $content, "From: noreply@instagrume.com\r\nContent-type:text/html;charset=UTF-8\r\n");
				break ;
			}
			case Utils::FORGOT_TYPE : {
				// get template and replace variable
				$content = file_get_contents('./mail_template/forgot.html');
				$content = preg_replace("/%name%/", $user->name, $content);
				$content = preg_replace("/%password%/", $other, $content);
				// send mail
				mail($user->mail, "[Instagrume] Your new password is here !", $content, "From: noreply@instagrume.com\r\nContent-type:text/html;charset=UTF-8\r\n");
				break ;
			}
		}
	}

}
?>
