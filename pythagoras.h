/*
 * pythagoras.h
 *
 * Header file for pythagoras.
 *
 * Author: Jeffrey Picard
 */
/* prompt.c */
void print_prompt( void );
char *get_input( FILE* );
int parse_input( char* );
int parse_delimited_cmds( char *, char, char *** );
void print_array_strings( char **, int );
void delete_cmds( char ** );

void *pythagoras_os_cmd( void*, void* );
void *exit_func( void*, void* );
void *help_func( void *, void * );

/* Macros */
#define EXIT_WITH_ERROR( ... ) do {   \
  fprintf( stderr, __VA_ARGS__ );     \
  exit(-1);                           \
} while( 0 ) 

#define MALLOC_CHECK( p, ... )  do {  \
  if( !p )                            \
    EXIT_WITH_ERROR( __VA_ARGS__ );   \
} while( 0 )

#define DEBUG_PARSING 0

