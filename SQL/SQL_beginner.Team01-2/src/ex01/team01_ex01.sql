SELECT
    COALESCE(u.name, 'not defined') AS name,
    COALESCE(u.lastname, 'not defined') AS lastname, cr.name AS currency_name, 
	cr.money * COALESCE(min, max) AS currency_in_usd
FROM (
	SELECT b.user_id, c.id, c.name, b.money, (
		SELECT c.rate_to_usd
		FROM currency c
		WHERE c.id = b.currency_id AND c.updated < b.updated
		ORDER BY rate_to_usd
		LIMIT 1
	) AS min, (
		SELECT c.rate_to_usd
		FROM currency c
		WHERE c.id = b.currency_id AND c.updated > b.updated
		ORDER BY rate_to_usd
		LIMIT 1
	) AS max
		FROM currency c
        JOIN balance b ON c.id = b.currency_id
        GROUP BY b.money, c.name, c.id, b.updated, b.currency_id, b.user_id
        ORDER BY min DESC, max, b.updated
    ) AS cr
LEFT JOIN "user" u ON cr.user_id = u.id
ORDER BY name DESC, lastname, currency_name;