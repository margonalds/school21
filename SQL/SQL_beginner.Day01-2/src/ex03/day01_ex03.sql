SELECT order_date AS action_date, person_id
FROM person_order
WHERE EXISTS (
	SELECT 1
	FROM person_visits
	WHERE person_visits.visit_date = person_order.order_date
	AND person_visits.person_id = person_order.person_id
)
UNION
SELECT visit_date AS action_date, person_id
FROM person_visits
WHERE EXISTS (
	SELECT 1
	FROM person_order
	WHERE person_visits.visit_date = person_order.order_date
	AND person_visits.person_id = person_order.person_id
)
ORDER BY action_date ASC,
	person_id DESC;