SELECT address, pz.name, COUNT(po.id) AS count_of_orders
FROM person p 
JOIN person_order po ON p.id = po.person_id
JOIN menu m ON po.menu_id = m.id
JOIN pizzeria pz ON pz.id = m.pizzeria_id
GROUP BY address, pz.name
ORDER BY address, pz.name