MODULES = pg_postal_code_ca
EXTENSION = pg_postal_code_ca
DATA = pg_postal_code_ca--1.0.sql
DOCS = README.pg_postal_code_ca

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
