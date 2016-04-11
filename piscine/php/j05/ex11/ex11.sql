SELECT * FROM `fiche_personne` LEFT JOIN membre ON fiche_personne.id_perso = membre.id_fiche_perso WHERE membre.id_abo != 3 AND membre.id_abo != 2 ORDER BY `nom`,`prenom`;
