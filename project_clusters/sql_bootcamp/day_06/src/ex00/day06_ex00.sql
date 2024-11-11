CREATE TABLE person_discounts (
    id BIGINT PRIMARY KEY,
    person_id BIGINT NOT NULL,
    pizzeria_id BIGINT NOT NULL,
    discount NUMERIC,
    -- Linking tables fields.
    CONSTRAINT fk_person_discounts_person_id FOREIGN KEY (person_id) REFERENCES person (id),
    CONSTRAINT fk_person_discounts_pizzeria_id FOREIGN KEY (pizzeria_id) REFERENCES pizzeria (id)
);
