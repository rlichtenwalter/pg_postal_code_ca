MODULES = pg_postal_code_CA
EXTENSION = pg_postal_code_CA
DATA = pg_postal_code_CA--1.0.sql
DOCS = README.pg_postal_code_CA

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
