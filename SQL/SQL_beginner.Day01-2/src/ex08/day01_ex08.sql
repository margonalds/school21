SELECT 
    po.order_date, 
    CONCAT(p.name, ' (age:', p.age, ')') AS person_information
FROM 
    person_order po
NATURAL JOIN 
    person p
ORDER BY 
    po.order_date ASC, 
    person_information ASC;