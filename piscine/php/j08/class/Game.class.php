<?PHP
	require_once 'Player.class.php';
	
	class Game {
		
		protected $_id = 0;
		protected $_players = array();

		static function load($id) {
			if (file_exists("../../datas/parties/". $id) == false)
				return null;
			$content = unserialize(file_get_contents("../../datas/parties/" . $id));
			$instance = new GameManager();
			$instance.set_players($content['_players']);
			$instance.set_id($id);
			$instance.set_turn($content['_turn']);
			return $instance;
		}

		public function save() {
			file_put_contents("../../datas/parties/" . $this->_id, serialize($this));				
		}

  		public static function gen_uuid() {
    		return sprintf('%04x%04x-%04x-%04x-%04x-%04x%04x%04x',
      			mt_rand(0, 0xffff), mt_rand(0, 0xffff), mt_rand(0, 0xffff),
      			mt_rand(0, 0x0fff) | 0x4000, mt_rand(0, 0x3fff) | 0x8000,
      			mt_rand(0, 0xffff), mt_rand(0, 0xffff), mt_rand(0, 0xffff));
		}						
    
		public function getId() {
			return $this->_id;
		}
		
		public function getPlayers() {
			return $this->_players;
		}
	}
?>
