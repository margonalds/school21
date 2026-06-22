WITH RECURSIVE tsp (tour, last, total_cost, visited) AS (
    SELECT 
        ARRAY['a']::TEXT[], 
        'a'::TEXT, 
        0, 
        ARRAY['a']::TEXT[]
    UNION ALL
    SELECT 
        tsp.tour || c.point2::TEXT,
        c.point2::TEXT,
        tsp.total_cost + c.cost,
        tsp.visited || c.point2::TEXT
    FROM tsp
    JOIN cities c ON tsp.last = c.point1
    WHERE NOT c.point2 = ANY(tsp.visited)
),
complete_tours AS (
    SELECT 
        tsp.tour || 'a'::TEXT AS tour, 
        tsp.total_cost + c.cost AS total_cost
    FROM tsp
    JOIN cities c ON tsp.last = c.point1
    WHERE c.point2 = 'a' AND array_length(tsp.visited, 1) = 4
),
min_cost AS (
    SELECT MIN(total_cost) AS min_total_cost FROM complete_tours
),
max_cost AS (
    SELECT MAX(total_cost) AS max_total_cost FROM complete_tours
)
SELECT ct.total_cost, ct.tour
FROM complete_tours ct
JOIN min_cost mc ON ct.total_cost = mc.min_total_cost
UNION ALL
SELECT ct.total_cost, ct.tour
FROM complete_tours ct
JOIN max_cost xc ON ct.total_cost = xc.max_total_cost
ORDER BY total_cost, tour;