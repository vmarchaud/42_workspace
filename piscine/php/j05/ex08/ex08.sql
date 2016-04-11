SELECT `nom`, `prenom`, date(`date_naissance`) FROM `fiche_personne` WHERE `date_naissance` LIKE '1989%' ORDER BY `nom`;
