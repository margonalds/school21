SELECT 
    m.pizza_name,
    pz.name AS pizzeria_name,
    m.price
FROM pizzeria pz
JOIN menu m ON pz.id = m.pizzeria_id
WHERE m.pizza_name IN ('mushroom pizza', 'pepperoni pizza')
ORDER BY m.pizza_name, pz.name;