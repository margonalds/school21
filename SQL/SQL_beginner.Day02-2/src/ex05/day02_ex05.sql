WITH param AS (
	SELECT age, gender, name
	FROM person
	WHERE age > 25 AND gender = 'female'
)
SELECT name
FROM param
ORDER BY name;