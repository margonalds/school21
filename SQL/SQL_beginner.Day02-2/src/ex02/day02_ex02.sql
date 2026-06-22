WITH filtered_visits AS (
    SELECT *
    FROM person_visits
    WHERE visit_date BETWEEN '2022-01-01' AND '2022-01-03'
)
SELECT
    COALESCE(p.name, '-') AS person_name,
    fv.visit_date,
    COALESCE(pz.name, '-') AS pizzeria_name
FROM filtered_visits fv
FULL OUTER JOIN person p ON fv.person_id = p.id
FULL OUTER JOIN pizzeria pz ON fv.pizzeria_id = pz.id
ORDER BY
    person_name ASC,
    visit_date ASC,
    pizzeria_name ASC;