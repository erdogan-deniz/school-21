-- A "COMMENT ON TABLE" is used to add a description of the table elements.
COMMENT ON TABLE person_discounts IS 
    'The table of discounts for persons in relation to restaurants.';

COMMENT ON COLUMN person_discounts.id IS 
    'A primary key for the person discount.';

COMMENT ON COLUMN person_discounts.person_id IS 
    'A foreign key referencing the "person" table. Identifies the individual for whom the discount is applicable.';

COMMENT ON COLUMN person_discounts.pizzeria_id IS 
    'A foreign key referencing the "pizzeria" table. Identifies the pizzeria where the discount is applicable.';

COMMENT ON COLUMN person_discounts.discount IS 
    'The percentage discount amount for a person at a certain restaurant. It ranges from 0 to 100.';
