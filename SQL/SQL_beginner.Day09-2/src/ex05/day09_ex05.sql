DROP FUNCTION IF EXISTS fnc_persons_female();
DROP FUNCTION IF EXISTS fnc_persons_male();

CREATE FUNCTION fnc_persons(pgender VARCHAR DEFAULT 'female')
RETURNS TABLE (id BIGINT, name VARCHAR, age INTEGER, gender VARCHAR, address VARCHAR) AS $$
	SELECT id, name, age, gender, address 
	FROM person
	WHERE gender = pgender;
$$ LANGUAGE SQL;

SELECT * 
FROM fnc_persons (pgender := 'male');

SELECT * 
FROM fnc_persons ();