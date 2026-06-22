SELECT p.name
FROM person p
JOIN person_order po ON p.id = po.person_id
JOIN menu ON po.menu_id = menu.id
JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
WHERE p.gender = 'male'
	AND p.address IN ('Moscow', 'Samara')
	AND menu.pizza_name IN ('pepperoni pizza', 'mushroom pizza')
ORDER BY p.name DESC;