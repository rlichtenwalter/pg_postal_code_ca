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

PG_FUNCTION_INFO_V1( canadian_postal_code_in );
Datum canadian_postal_code_in( PG_FUNCTION_ARGS ) {
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

PG_FUNCTION_INFO_V1( canadian_postal_code_out );
Datum canadian_postal_code_out( PG_FUNCTION_ARGS ) {
	char const * canadian_postal_code;
	canadian_postal_code = PG_GETARG_CSTRING( 0 );
	PG_RETURN_CSTRING( canadian_postal_code );
}

PG_FUNCTION_INFO_V1( canadian_postal_code_cmp );
Datum canadian_postal_code_cmp( PG_FUNCTION_ARGS ) {
	char const * a;
	char const * b;
	a = PG_GETARG_CSTRING( 0 );
	b = PG_GETARG_CSTRING( 1 );
	PG_RETURN_INT32( strcmp( a, b ) );
}

PG_FUNCTION_INFO_V1( canadian_postal_code_lt );
Datum canadian_postal_code_lt( PG_FUNCTION_ARGS ) {
	char const * a;
	char const * b;
	a = PG_GETARG_CSTRING( 0 );
	b = PG_GETARG_CSTRING( 1 );
	PG_RETURN_BOOL( strcmp( a, b ) < 0 );
}

PG_FUNCTION_INFO_V1( canadian_postal_code_le );
Datum canadian_postal_code_le( PG_FUNCTION_ARGS ) {
	char const * a;
	char const * b;
	a = PG_GETARG_CSTRING( 0 );
	b = PG_GETARG_CSTRING( 1 );
	PG_RETURN_BOOL( strcmp( a, b ) <= 0 );
}

PG_FUNCTION_INFO_V1( canadian_postal_code_eq );
Datum canadian_postal_code_eq( PG_FUNCTION_ARGS ) {
	char const * a;
	char const * b;
	a = PG_GETARG_CSTRING( 0 );
	b = PG_GETARG_CSTRING( 1 );
	PG_RETURN_BOOL( strcmp( a, b ) == 0 );
}

PG_FUNCTION_INFO_V1( canadian_postal_code_ge );
Datum canadian_postal_code_ge( PG_FUNCTION_ARGS ) {
	char const * a;
	char const * b;
	a = PG_GETARG_CSTRING( 0 );
	b = PG_GETARG_CSTRING( 1 );
	PG_RETURN_BOOL( strcmp( a, b ) >= 0 );
}

PG_FUNCTION_INFO_V1( canadian_postal_code_gt );
Datum canadian_postal_code_gt( PG_FUNCTION_ARGS ) {
	char const * a;
	char const * b;
	a = PG_GETARG_CSTRING( 0 );
	b = PG_GETARG_CSTRING( 1 );
	PG_RETURN_BOOL( strcmp( a, b ) > 0 );
}

PG_FUNCTION_INFO_V1( canadian_postal_code_ne );
Datum canadian_postal_code_ne( PG_FUNCTION_ARGS ) {
	char const * a;
	char const * b;
	a = PG_GETARG_CSTRING( 0 );
	b = PG_GETARG_CSTRING( 1 );
	PG_RETURN_BOOL( strcmp( a, b ) != 0 );
}
