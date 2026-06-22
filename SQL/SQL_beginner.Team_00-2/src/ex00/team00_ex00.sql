CREATE TABLE cities (
	point1 VARCHAR(1),
	point2 VARCHAR(1),
	cost INT
);

INSERT INTO cities (point1, point2, cost) VALUES
	('a', 'b', 10),
	('b', 'a', 10),
	('a', 'c', 15),
	('c', 'a', 15),
	('a', 'd', 20),
	('d', 'a', 20),
	('b', 'c', 35),
	('c', 'b', 35),
	('b', 'd', 25),
	('d', 'b', 25),
	('c', 'd', 30),
	('d', 'c', 30);

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
)
SELECT ct.total_cost, ct.tour
FROM complete_tours ct
JOIN min_cost mc ON ct.total_cost = mc.min_total_cost
ORDER BY ct.total_cost, ct.tour;