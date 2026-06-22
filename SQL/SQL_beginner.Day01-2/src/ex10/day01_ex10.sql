SELECT 
	p.name AS person_name,
	m.pizza_name,
	pi.name AS pizzeria_name
FROM person_order po
	JOIN person p ON po.person_id = p.id
	JOIN menu m ON po.menu_id = m.id
	JOIN pizzeria pi ON m.pizzeria_id = pi.id
ORDER BY
	person_name ASC, 
    pizza_name ASC, 
    pizzeria_name ASC;