WITH all_days AS (
    SELECT generate_series(
        '2022-01-01'::DATE,
        '2022-01-10'::DATE,
        '1 day'::INTERVAL
    )::DATE AS missing_date
)
SELECT ad.missing_date
FROM all_days ad
LEFT JOIN person_visits pv
    ON ad.missing_date = pv.visit_date
    AND pv.person_id IN (1, 2)
WHERE pv.person_id IS NULL
ORDER BY ad.missing_date ASC;