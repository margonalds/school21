WITH visits AS (
	SELECT pz.name, COUNT(*) AS count, 'visit' AS action_type
	FROM person_visits pv
	JOIN pizzeria pz on pv.pizzeria_id = pz.id
	GROUP BY pz.name
	LIMIT 3
), 
orders AS (
	SELECT pz.name, COUNT(*) AS count, 'order' AS action_type
	FROM person_order po
	JOIN menu m ON po.menu_id = m.id
	JOIN pizzeria pz on m.pizzeria_id = pz.id
	GROUP BY pz.name
	LIMIT 3
)
SELECT name, count, action_type
FROM visits
UNION ALL
SELECT name, count, action_type
FROM orders
ORDER BY action_type ASC, count DESC