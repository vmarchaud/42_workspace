
--
-- Base de données :  `camagru`
--

-- --------------------------------------------------------

--
-- Structure de la table `comments`
--

CREATE TABLE IF NOT EXISTS `comments` (
  `id` varchar(36) NOT NULL,
  `post` varchar(36) DEFAULT NULL,
  `author` varchar(36) DEFAULT NULL,
  `state` enum('SHOWN','DELETED','EDITED','MODERATED') NOT NULL DEFAULT 'SHOWN',
  `content` text,
  `date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

DELETE FROM `comments` WHERE 1;

-- --------------------------------------------------------

--
-- Structure de la table `posts`
--

CREATE TABLE IF NOT EXISTS `posts` (
  `id` varchar(36) NOT NULL,
  `author` varchar(36) DEFAULT NULL,
  `img` longtext,
  `date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

DELETE FROM `posts` WHERE 1;

-- --------------------------------------------------------

--
-- Structure de la table `users`
--

CREATE TABLE IF NOT EXISTS `users` (
  `id` varchar(36) NOT NULL,
  `mail` text,
  `name` text,
  `password` text,
  `role` enum('USER','ADMIN','MODERATOR') DEFAULT 'USER',
  `state` enum('NEED_VALIDATION','FORGET_PASSWD','REGISTERED','DELETED') NOT NULL DEFAULT 'NEED_VALIDATION'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

DELETE FROM `users` WHERE 1;

-- --------------------------------------------------------

--
-- Structure de la table `likes`
--

CREATE TABLE IF NOT EXISTS `likes` (
  `post` varchar(36) NOT NULL,
  `user` varchar(36) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

DELETE FROM `likes` WHERE 1;

-- --------------------------------------------------------

--
-- Structure de la table `tokens`
--

CREATE TABLE IF NOT EXISTS `tokens` (
  `id` varchar(36) NOT NULL,
  `user` varchar(36) DEFAULT NULL,
  `type` enum('FORGOT_PASSWORD','REGISTER') DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

DELETE FROM `tokens` WHERE 1;

--
-- Index pour les tables exportées
--

--
-- Index pour la table `comments`
--
ALTER TABLE `comments`
 ADD PRIMARY KEY (`id`);

--
-- Index pour la table `posts`
--
ALTER TABLE `posts`
 ADD PRIMARY KEY (`id`);

--
-- Index pour la table `users`
--
ALTER TABLE `users`
 ADD PRIMARY KEY (`id`);

--
-- Index pour la table `tokens`
--
ALTER TABLE `tokens`
 ADD PRIMARY KEY (`id`);
