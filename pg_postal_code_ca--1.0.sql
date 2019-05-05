CREATE TYPE postal_code_ca;

CREATE OR REPLACE FUNCTION postal_code_ca_in( CSTRING )
	RETURNS postal_code_ca
	AS 'MODULE_PATHNAME'
	LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION postal_code_ca_out( postal_code_ca )
	RETURNS CSTRING
	AS 'MODULE_PATHNAME'
	LANGUAGE C IMMUTABLE STRICT;

CREATE TYPE postal_code_ca (
	INPUT = postal_code_ca_in,
	OUTPUT = postal_code_ca_out,
	INTERNALLENGTH = 8,
	PASSEDBYVALUE = FALSE,
	ALIGNMENT = char,
	STORAGE = plain
);

CREATE FUNCTION postal_code_ca_lt( postal_code_ca, postal_code_ca )
	RETURNS BOOL
	AS 'MODULE_PATHNAME'
	LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION postal_code_ca_le( postal_code_ca, postal_code_ca )
	RETURNS BOOL
	AS 'MODULE_PATHNAME'
	LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION postal_code_ca_eq( postal_code_ca, postal_code_ca )
	RETURNS BOOL
	AS 'MODULE_PATHNAME'
	LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION postal_code_ca_ge( postal_code_ca, postal_code_ca )
	RETURNS BOOL
	AS 'MODULE_PATHNAME'
	LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION postal_code_ca_gt( postal_code_ca, postal_code_ca )
	RETURNS BOOL
	AS 'MODULE_PATHNAME'
	LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION postal_code_ca_ne( postal_code_ca, postal_code_ca )
	RETURNS BOOL
	AS 'MODULE_PATHNAME'
	LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE OPERATOR < (
	LEFTARG = postal_code_ca,
	RIGHTARG = postal_code_ca,
	PROCEDURE = postal_code_ca_lt,
	COMMUTATOR = >,
	NEGATOR = >=,
	RESTRICT = scalarltsel,
	JOIN = scalarltjoinsel
);

CREATE OPERATOR <= (
	LEFTARG = postal_code_ca,
	RIGHTARG = postal_code_ca,
	PROCEDURE = postal_code_ca_le,
	COMMUTATOR = >=,
	NEGATOR = >,
	RESTRICT = scalarltsel,
	JOIN = scalarltjoinsel
);

CREATE OPERATOR = (
	LEFTARG = postal_code_ca,
	RIGHTARG = postal_code_ca,
	PROCEDURE = postal_code_ca_eq,
	COMMUTATOR = =,
	NEGATOR = <>,
	RESTRICT = eqsel,
	JOIN = eqjoinsel
);

CREATE OPERATOR >= (
	LEFTARG = postal_code_ca,
	RIGHTARG = postal_code_ca,
	PROCEDURE = postal_code_ca_ge,
	COMMUTATOR = <=,
	NEGATOR = <,
	RESTRICT = scalargtsel,
	JOIN = scalargtjoinsel
);

CREATE OPERATOR > (
	LEFTARG = postal_code_ca,
	RIGHTARG = postal_code_ca,
	PROCEDURE = postal_code_ca_gt,
	COMMUTATOR = <,
	NEGATOR = <=,
	RESTRICT = scalargtsel,
	JOIN = scalargtjoinsel
);

CREATE OPERATOR <> (
	LEFTARG = postal_code_ca,
	RIGHTARG = postal_code_ca,
	PROCEDURE = postal_code_ca_ne,
	COMMUTATOR = <>,
	NEGATOR = =,
	RESTRICT = neqsel,
	JOIN = neqjoinsel
);

CREATE FUNCTION postal_code_ca_cmp( postal_code_ca, postal_code_ca )
	RETURNS INTEGER
	AS 'MODULE_PATHNAME'
	LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE OPERATOR CLASS postal_code_ca_ops
	DEFAULT FOR TYPE postal_code_ca USING BTREE AS
	OPERATOR 1 <,
	OPERATOR 2 <=,
	OPERATOR 3 =,
	OPERATOR 4 >=,
	OPERATOR 5 >,
	FUNCTION 1 postal_code_ca_cmp( postal_code_ca, postal_code_ca );
