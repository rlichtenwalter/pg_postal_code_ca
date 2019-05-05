#include <postgres.h>
#include <fmgr.h>
#include <stdint.h>
#include <stdio.h>
#include <regex.h>
#include <ctype.h>
#include <string.h>

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

#define NUM_CAPTURES 16
#define MESSAGE_BUFFER_SIZE 256

PG_FUNCTION_INFO_V1( postal_code_ca_in );
Datum postal_code_ca_in( PG_FUNCTION_ARGS ) {
	char const * str;
	char const * regex_str;
	regex_t regex;
	regmatch_t captures[NUM_CAPTURES];
	int compile_code;
	char message_buffer[MESSAGE_BUFFER_SIZE];
	int buffer_required;
	int exec_code;
	char const * result;
	str = PG_GETARG_CSTRING( 0 );
	regex_str = "^\\([a-zA-Z][0-9][a-zA-Z]\\) \\?\\([0-9][a-zA-Z][0-9]\\)$";
	compile_code = regcomp( &regex, regex_str, 0 );
	if( compile_code ) {
		buffer_required = regerror( compile_code, &regex, message_buffer, MESSAGE_BUFFER_SIZE );
		(void)buffer_required; // do not use the return value for now
		ereport( ERROR, (errcode(ERRCODE_EXTERNAL_ROUTINE_EXCEPTION),errmsg( "regular expression compilation failed: %s in '%s'\n", message_buffer, regex_str )) );
	}
	exec_code = regexec( &regex, str, NUM_CAPTURES, captures, 0 );
	if( !exec_code ) {
		result = psprintf( "%c%c%c %c%c%c",
				toupper( str[ captures[1].rm_so + 0 ] ),
				str[ captures[1].rm_so + 1 ],
				toupper( str[ captures[1].rm_so + 2 ] ),
				str[ captures[2].rm_so + 0 ],
				toupper( str[ captures[2].rm_so + 1 ] ),
				str[ captures[2].rm_so + 2 ]
				 );
		PG_RETURN_CSTRING( result );
	} else if( exec_code == REG_NOMATCH ) {
		ereport( ERROR, (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),errmsg("invalid input format for candian_postal_code: '%s'", str)) );
	} else {
		buffer_required = regerror( compile_code, &regex, message_buffer, MESSAGE_BUFFER_SIZE );
		(void)buffer_required; // do not use the return value for now
		ereport( ERROR, (errcode(ERRCODE_EXTERNAL_ROUTINE_EXCEPTION),errmsg( "unexpected error: %s executing '%s' on '%s'", message_buffer, regex_str, str )) );
	}
	regfree( &regex );
}

PG_FUNCTION_INFO_V1( postal_code_ca_out );
Datum postal_code_ca_out( PG_FUNCTION_ARGS ) {
	char const * postal_code_ca;
	postal_code_ca = PG_GETARG_CSTRING( 0 );
	PG_RETURN_CSTRING( postal_code_ca );
}

PG_FUNCTION_INFO_V1( postal_code_ca_cmp );
Datum postal_code_ca_cmp( PG_FUNCTION_ARGS ) {
	char const * a;
	char const * b;
	a = PG_GETARG_CSTRING( 0 );
	b = PG_GETARG_CSTRING( 1 );
	PG_RETURN_INT32( strcmp( a, b ) );
}

PG_FUNCTION_INFO_V1( postal_code_ca_lt );
Datum postal_code_ca_lt( PG_FUNCTION_ARGS ) {
	char const * a;
	char const * b;
	a = PG_GETARG_CSTRING( 0 );
	b = PG_GETARG_CSTRING( 1 );
	PG_RETURN_BOOL( strcmp( a, b ) < 0 );
}

PG_FUNCTION_INFO_V1( postal_code_ca_le );
Datum postal_code_ca_le( PG_FUNCTION_ARGS ) {
	char const * a;
	char const * b;
	a = PG_GETARG_CSTRING( 0 );
	b = PG_GETARG_CSTRING( 1 );
	PG_RETURN_BOOL( strcmp( a, b ) <= 0 );
}

PG_FUNCTION_INFO_V1( postal_code_ca_eq );
Datum postal_code_ca_eq( PG_FUNCTION_ARGS ) {
	char const * a;
	char const * b;
	a = PG_GETARG_CSTRING( 0 );
	b = PG_GETARG_CSTRING( 1 );
	PG_RETURN_BOOL( strcmp( a, b ) == 0 );
}

PG_FUNCTION_INFO_V1( postal_code_ca_ge );
Datum postal_code_ca_ge( PG_FUNCTION_ARGS ) {
	char const * a;
	char const * b;
	a = PG_GETARG_CSTRING( 0 );
	b = PG_GETARG_CSTRING( 1 );
	PG_RETURN_BOOL( strcmp( a, b ) >= 0 );
}

PG_FUNCTION_INFO_V1( postal_code_ca_gt );
Datum postal_code_ca_gt( PG_FUNCTION_ARGS ) {
	char const * a;
	char const * b;
	a = PG_GETARG_CSTRING( 0 );
	b = PG_GETARG_CSTRING( 1 );
	PG_RETURN_BOOL( strcmp( a, b ) > 0 );
}

PG_FUNCTION_INFO_V1( postal_code_ca_ne );
Datum postal_code_ca_ne( PG_FUNCTION_ARGS ) {
	char const * a;
	char const * b;
	a = PG_GETARG_CSTRING( 0 );
	b = PG_GETARG_CSTRING( 1 );
	PG_RETURN_BOOL( strcmp( a, b ) != 0 );
}
