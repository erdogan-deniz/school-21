WITH cte_latest_updated AS(		-- таблица, в которой rate_to_usd помечен цифрами по новизне (1 - самый новый)
	SELECT
		cu.id,
		cu.rate_to_usd,
		ROW_NUMBER() OVER (PARTITION BY cu.id ORDER BY cu.updated DESC) AS rn
	FROM currency cu
)

SELECT
	COALESCE (us.name, 'not defined') AS name,
	COALESCE (us.lastname, 'not defined') AS lastname,
	ba.type AS type,
	SUM(ba.money) AS volume,
	COALESCE(
		(SELECT DISTINCT c.name FROM currency c WHERE c.id = ba.currency_id),
		'not defined') AS currency_name,
	COALESCE(clu.rate_to_usd, 1) AS last_rate_to_usd,
	(SUM(ba.money) * COALESCE(clu.rate_to_usd, 1)) AS total_volume_in_usd
FROM balance ba
LEFT JOIN "user" us ON us.id = ba.user_id
LEFT JOIN cte_latest_updated clu ON ba.currency_id = clu.id AND clu.rn = 1
GROUP BY
	us.id,
	ba.type,
	currency_name,
	last_rate_to_usd
ORDER BY name DESC, lastname ASC, ba.type ASC;