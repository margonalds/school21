CREATE OR REPLACE FUNCTION func_minimum (arr NUMERIC[])
RETURNS NUMERIC AS $$
SELECT MIN(unnested)
FROM unnest(arr) as unnested;
$$ LANGUAGE SQL;

SELECT func_minimum(VARIADIC arr => ARRAY[10.0, -1.0, 5.0, 4.4]);