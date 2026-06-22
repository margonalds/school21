SELECT DISTINCT pz.name AS pizzeria_name
FROM person_visits pv
JOIN pizzeria pz ON pv.pizzeria_id = pz.id
WHERE pv.person_id = (
	SELECT id
	FROM person 
	WHERE name = 'Andrey'
)
AND pz.id NOT IN (
	SELECT DISTINCT m.pizzeria_id
	FROM menu m 
	JOIN person_order po ON m.id = po.menu_id
	WHERE po.person_id = (
		SELECT id
		FROM person
		WHERE name = 'Andrey'
	)
)
ORDER BY pizzeria_name;