SELECT pizza_name, price, (
	SELECT name
	FROM pizzeria
	WHERE pizzeria.id = menu.pizzeria_id
) AS pizzeria_name
FROM menu  
WHERE id NOT IN (
	SELECT menu_id
	FROM person_order
)
ORDER BY pizza_name, price;