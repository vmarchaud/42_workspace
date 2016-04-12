SELECT DATEDIFF(MAX(DATE(`date`)), MIN(DATE(`date`))) AS 'uptime' FROM `historique_membre` GROUP BY `id_film`;
