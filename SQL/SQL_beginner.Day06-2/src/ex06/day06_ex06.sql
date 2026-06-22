CREATE SEQUENCE seq_person_discount
START WITH 1;

SELECT setval ('seq_person_discount', COALESCE(MAX(id), 0) + 1)
FROM person_discounts;

ALTER TABLE person_discounts
ALTER COLUMN id
SET DEFAULT nextval('seq_person_discount');