SELECT pizzeria_name
FROM (
	SELECT pv.pizzeria_id,
		pz.name AS pizzeria_name,
		SUM(CASE WHEN p.gender = 'female' THEN 1 ELSE 0 END) 
		AS female_visits,
		SUM(CASE WHEN p.gender = 'male' THEN 1 ELSE 0 END) 
		AS male_visits
	FROM person_visits pv
	JOIN person p ON pv.person_id = p.id
	JOIN pizzeria pz ON pv.pizzeria_id = pz.id
	GROUP BY pv.pizzeria_id, pz.name
) visits_comparsion
WHERE female_visits > male_visits OR male_visits > female_visits
ORDER BY pizzeria_name