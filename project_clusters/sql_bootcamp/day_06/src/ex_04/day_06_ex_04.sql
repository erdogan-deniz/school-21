-- An "ALTER TABLE" is used to change table constraints or table structure.
ALTER TABLE person_discounts  -- A "CHECK()" is used to set limits on values.
    ADD CONSTRAINT ch_nn_person_id CHECK (person_id IS NOT NULL),
    ADD CONSTRAINT ch_nn_pizzeria_id CHECK (pizzeria_id IS NOT NULL),
    ALTER COLUMN discount
        SET DEFAULT 0,
    ADD CONSTRAINT ch_nn_discount CHECK (discount IS NOT NULL),
    ADD CONSTRAINT ch_range_discount CHECK (discount BETWEEN 0 AND 100);
