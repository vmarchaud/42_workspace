INSERT INTO ft_table (login, date_de_creation) SELECT nom,date_naissance FROM fiche_personne WHERE nom LIKE '%a%' AND LENGTH(nom) < 9 ORDER BY nom LIMIT 10;
