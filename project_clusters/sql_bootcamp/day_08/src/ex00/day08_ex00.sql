-- Session № 1:
-- SELECT pg_backend_pid();
BEGIN;  -- Action № 1
UPDATE pizzeria SET rating = 5 WHERE name = 'Pizza Hut';  -- Action № 2
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';  -- Action № 3
COMMIT;  -- Action № 5

-- Session № 2:
-- SELECT pg_backend_pid();
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';  -- Action № 4
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';  -- Action № 6
