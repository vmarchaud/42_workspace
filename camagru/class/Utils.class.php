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

	// function used to send a mail to an user
	public static function sendMail($type, $user) {
		switch($type) {
			case VALID_TYPE : {
				// send valid type
				break ;
			}
			case FORGOT_TYPE : {
				// send forgot type
				break ; 
			}
		}
	}

}
?>
