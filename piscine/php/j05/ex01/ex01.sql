CREATE TABLE IF NOT EXISTS ft_table
(
	id INTEGER NOT NULL PRIMARY KEY AUTO_INCREMENT,
	login VARCHAR(8) DEFAULT 'toto',
	groupe ENUM('staff', 'student', 'other') NOT NULL,
	date_de_creation DATE NOT NULL

);
