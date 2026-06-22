WITH visits AS (
	SELECT pz.name, COUNT(*) AS visit_count
	FROM person_visits pv
	JOIN pizzeria pz on pv.pizzeria_id = pz.id
	GROUP BY pz.name
), 
orders AS (
	SELECT pz.name, COUNT(*) AS order_count
	FROM person_order po
	JOIN menu m ON po.menu_id = m.id
	JOIN pizzeria pz on m.pizzeria_id = pz.id
	GROUP BY pz.name
)
SELECT 
    COALESCE(oc.name, vc.name) AS name,
    COALESCE(order_count, 0) + COALESCE(visit_count, 0) AS total_count
FROM orders oc
FULL JOIN visits vc ON oc.name = vc.name
ORDER BY total_count DESC, name ASC;