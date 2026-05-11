# Reproducible SQL Bootcamp run-it-locally workflow.
# See docker-compose.yml for the Postgres service contract.

DAY        ?= 00
DB          = bootcamp
USER        = school21
DAYS_ALL    = 00 01 02 03 04 05 06 07 08 09

COMPOSE     = docker compose

# Locate the schema file for the requested day. Days differ in folder
# convention — some put model.sql under materials/, others under resources/.
MODEL_PATH  = $(shell \
                if [ -f day_$(DAY)/materials/model.sql ]; then \
                    echo /workspace/day_$(DAY)/materials/model.sql; \
                elif [ -f day_$(DAY)/resources/model.sql ]; then \
                    echo /workspace/day_$(DAY)/resources/model.sql; \
                fi)

.PHONY: up down seed psql test-all clean help

help:                  ## Show this help.
	@awk 'BEGIN {FS = ":.*## "} /^[a-zA-Z_-]+:.*## / {printf "  %-12s %s\n", $$1, $$2}' $(MAKEFILE_LIST)

up:                    ## Start postgres and block until healthy.
	$(COMPOSE) up -d
	@echo "Waiting for postgres to be ready..."
	@for _ in $$(seq 1 30); do \
	    $(COMPOSE) exec -T postgres pg_isready -U $(USER) -d $(DB) > /dev/null 2>&1 && break; \
	    sleep 1; \
	done
	@echo "Postgres ready on localhost:5432 (db=$(DB), user=$(USER), pass=$(USER))"

seed: up               ## Load day_$$DAY/{materials,resources}/model.sql.
	@if [ -z "$(MODEL_PATH)" ]; then \
	    echo "No model.sql found for day_$(DAY)"; exit 1; \
	fi
	@echo "Seeding day_$(DAY) schema..."
	$(COMPOSE) exec -T postgres psql -U $(USER) -d $(DB) -v ON_ERROR_STOP=1 -f $(MODEL_PATH)
	@echo "Day $(DAY) schema loaded into the '$(DB)' database."

psql: seed             ## Open an interactive psql against the seeded DB.
	$(COMPOSE) exec postgres psql -U $(USER) -d $(DB)

test-all:              ## Drop + reseed every numbered day; bail on first failure.
	@set -e; \
	$(MAKE) up; \
	for d in $(DAYS_ALL); do \
	    echo "=== day_$$d ==="; \
	    $(COMPOSE) exec -T postgres psql -U $(USER) -d $(DB) -v ON_ERROR_STOP=1 \
	        -c "DROP SCHEMA public CASCADE; CREATE SCHEMA public;" > /dev/null; \
	    if [ -f day_$$d/materials/model.sql ]; then \
	        $(COMPOSE) exec -T postgres psql -U $(USER) -d $(DB) -v ON_ERROR_STOP=1 \
	            -f /workspace/day_$$d/materials/model.sql > /dev/null; \
	    elif [ -f day_$$d/resources/model.sql ]; then \
	        $(COMPOSE) exec -T postgres psql -U $(USER) -d $(DB) -v ON_ERROR_STOP=1 \
	            -f /workspace/day_$$d/resources/model.sql > /dev/null; \
	    else \
	        echo "  skip — no model.sql for day_$$d"; \
	    fi; \
	done
	@echo "All numbered days loaded cleanly."

down:                  ## Stop postgres and drop the volume.
	$(COMPOSE) down -v

clean: down            ## Alias for down.
