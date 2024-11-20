-- insert into currency values (100, 'EUR', 0.85, '2022-01-01 13:29');
-- insert into currency values (100, 'EUR', 0.79, '2022-01-08 13:29');

SELECT
	subquery.name AS name,
	subquery.lastname AS lastname,
	subquery.currency_name,
	subquery.money * subquery.rate_to_usd AS currency_in_usd
FROM (
	SELECT
		COALESCE(us.name, 'not defined') AS name,
		COALESCE(us.lastname, 'not defined') AS lastname,
		cu.name AS currency_name,
		ba.money AS money,
		COALESCE(
			(SELECT
				rate_to_usd
			FROM currency cu
			WHERE cu.updated < ba.updated AND ba.currency_id = cu.id
			ORDER BY cu.updated DESC LIMIT 1),
			(SELECT
				rate_to_usd
			FROM currency cu
			WHERE cu.updated > ba.updated AND ba.currency_id = cu.id
			ORDER BY cu.updated ASC LIMIT 1))
			AS rate_to_usd
	FROM balance ba
	FULL JOIN "user" us ON us.id = ba.user_id
	JOIN (SELECT DISTINCT id, name FROM currency) cu ON cu.id = ba.currency_id
) subquery
ORDER BY name DESC, lastname ASC, currency_name ASC;
