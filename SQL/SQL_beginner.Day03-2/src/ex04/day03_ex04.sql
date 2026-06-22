SELECT DISTINCT pz.name AS pizzeria_name
FROM pizzeria pz
WHERE pz.id IN(
	SELECT DISTINCT m.pizzeria_id
	FROM menu m
	JOIN person_order po ON m.id = po.menu_id
	JOIN person p ON po.person_id = p.id
	WHERE p.gender = 'female'
) 
AND pz.id NOT IN (
	SELECT DISTINCT m.pizzeria_id
	FROM menu m
	JOIN person_order po ON m.id = po.menu_id
	JOIN person p ON po.person_id = p.id
	WHERE p.gender = 'male'
)
UNION
SELECT DISTINCT pz.name AS pizzeria_name
FROM pizzeria pz
WHERE pz.id IN(
	SELECT DISTINCT m.pizzeria_id
	FROM menu m
	JOIN person_order po ON m.id = po.menu_id
	JOIN person p ON po.person_id = p.id
	WHERE p.gender = 'male'
) 
AND pz.id NOT IN (
	SELECT DISTINCT m.pizzeria_id
	FROM menu m
	JOIN person_order po ON m.id = po.menu_id
	JOIN person p ON po.person_id = p.id
	WHERE p.gender = 'female'
) 
ORDER BY pizzeria_name;