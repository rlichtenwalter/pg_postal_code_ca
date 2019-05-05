CREATE TYPE canadian_postal_code;

CREATE OR REPLACE FUNCTION canadian_postal_code_in( CSTRING )
	RETURNS canadian_postal_code
	AS 'MODULE_PATHNAME'
	LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION canadian_postal_code_out( canadian_postal_code )
	RETURNS CSTRING
	AS 'MODULE_PATHNAME'
	LANGUAGE C IMMUTABLE STRICT;

CREATE TYPE canadian_postal_code (
	INPUT = canadian_postal_code_in,
	OUTPUT = canadian_postal_code_out,
	INTERNALLENGTH = 8,
	PASSEDBYVALUE = FALSE,
	ALIGNMENT = char,
	STORAGE = plain
);

CREATE FUNCTION canadian_postal_code_lt( canadian_postal_code, canadian_postal_code )
	RETURNS BOOL
	AS 'MODULE_PATHNAME'
	LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION canadian_postal_code_le( canadian_postal_code, canadian_postal_code )
	RETURNS BOOL
	AS 'MODULE_PATHNAME'
	LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION canadian_postal_code_eq( canadian_postal_code, canadian_postal_code )
	RETURNS BOOL
	AS 'MODULE_PATHNAME'
	LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION canadian_postal_code_ge( canadian_postal_code, canadian_postal_code )
	RETURNS BOOL
	AS 'MODULE_PATHNAME'
	LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION canadian_postal_code_gt( canadian_postal_code, canadian_postal_code )
	RETURNS BOOL
	AS 'MODULE_PATHNAME'
	LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION canadian_postal_code_ne( canadian_postal_code, canadian_postal_code )
	RETURNS BOOL
	AS 'MODULE_PATHNAME'
	LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE OPERATOR < (
	LEFTARG = canadian_postal_code,
	RIGHTARG = canadian_postal_code,
	PROCEDURE = canadian_postal_code_lt,
	COMMUTATOR = >,
	NEGATOR = >=,
	RESTRICT = scalarltsel,
	JOIN = scalarltjoinsel
);

CREATE OPERATOR <= (
	LEFTARG = canadian_postal_code,
	RIGHTARG = canadian_postal_code,
	PROCEDURE = canadian_postal_code_le,
	COMMUTATOR = >=,
	NEGATOR = >,
	RESTRICT = scalarltsel,
	JOIN = scalarltjoinsel
);

CREATE OPERATOR = (
	LEFTARG = canadian_postal_code,
	RIGHTARG = canadian_postal_code,
	PROCEDURE = canadian_postal_code_eq,
	COMMUTATOR = =,
	NEGATOR = <>,
	RESTRICT = eqsel,
	JOIN = eqjoinsel
);

CREATE OPERATOR >= (
	LEFTARG = canadian_postal_code,
	RIGHTARG = canadian_postal_code,
	PROCEDURE = canadian_postal_code_ge,
	COMMUTATOR = <=,
	NEGATOR = <,
	RESTRICT = scalargtsel,
	JOIN = scalargtjoinsel
);

CREATE OPERATOR > (
	LEFTARG = canadian_postal_code,
	RIGHTARG = canadian_postal_code,
	PROCEDURE = canadian_postal_code_gt,
	COMMUTATOR = <,
	NEGATOR = <=,
	RESTRICT = scalargtsel,
	JOIN = scalargtjoinsel
);

CREATE OPERATOR <> (
	LEFTARG = canadian_postal_code,
	RIGHTARG = canadian_postal_code,
	PROCEDURE = canadian_postal_code_ne,
	COMMUTATOR = <>,
	NEGATOR = =,
	RESTRICT = neqsel,
	JOIN = neqjoinsel
);

CREATE FUNCTION canadian_postal_code_cmp( canadian_postal_code, canadian_postal_code )
	RETURNS INTEGER
	AS 'MODULE_PATHNAME'
	LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE OPERATOR CLASS canadian_postal_code_ops
	DEFAULT FOR TYPE canadian_postal_code USING BTREE AS
	OPERATOR 1 <,
	OPERATOR 2 <=,
	OPERATOR 3 =,
	OPERATOR 4 >=,
	OPERATOR 5 >,
	FUNCTION 1 canadian_postal_code_cmp( canadian_postal_code, canadian_postal_code );
