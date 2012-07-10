/*
 * prompt.c
 *
 * Prompt for pythagoras
 *
 * Author: Jeffrey Picard.
 */
/* Standard headers */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* My headers */
#include "pythagoras.h"

/* Constants */
#define NUM_CMDS 100
#define MAX_CMD_LEN 100
#define DEBUG 0


/* Structs */
struct _cmd_len {
  char cmd[NUM_CMDS][MAX_CMD_LEN];
  int len[NUM_CMDS];
  void* (*funcs[NUM_CMDS])( void* );
  int size;
} typedef cmd_len;

struct _cmd_info {
  int i;

} typedef cmd_info;

/****************** functions ***********************/

/*
 * print_prompt
 *
 * Prints a command line prompt for the user.
 */
void print_prompt( void )
{
  printf(">>> ");
}

/*
 * get_input
 *
 * Reads input from the given FILE* and return it as a string.
 */
char *get_input( FILE *fp )
{
  int buff_size = 100;
  char *buffer = calloc( buff_size, sizeof(char) );
  char c = 0;
  int i = 0;

  while( c != '\n' )
  {
    c = (char)fgetc( fp );
    buffer[i++] = c;
  }

  return buffer;
}

/*
 * parse_input
 *
 * Takes the user input as a string and attempts to parse it.
 *
 * Returns non-zero code indicating the result.
 * Returns zero on exit.
 */
int parse_input( char *input )
{
  cmd_len cmds = {
    {"zero","one","two","three", "exit"},
    {0,1,2,3,0},
    { func0, func1, func2, func3, exit_func },
    5
  };

  cmd_info *info = NULL;
  int l = strlen( input );
  int i = 0, j = 0;
  char c = 0;
  char *cmd = NULL;

  while( i < l )
  {
    c = input[i];
    if( ' ' == c || '\n' == c )
      break;
    else
      i++;
  }

  cmd = calloc( i+1, sizeof(char) );

  strncpy( cmd, input, i );

  for( j = 0; j < cmds.size; j++ )
  {
    if( 0 == strcmp( cmds.cmd[j], cmd ) )
    {
      info = (cmd_info*) cmds.funcs[j]( (void*)input );

      free( cmd );

      /* This will be NULL only if the exit command was given */
      if( !info )
        return 0;

      return 1;
    }
  }
  printf("Command '%s' not found!\n", cmd );

  free( cmd );
  return -1;
}

void *func0( void *args )
{
  printf("func0\n");

  return (void*)1;
}

void *func1( void *args )
{
  printf("func1\n");

  return (void*)1;
}

void *func2( void *args )
{
  printf("func2\n");
  
  return (void*)1;
}

void *func3( void *args )
{
  printf("func3\n");

  return (void*)1;
}

void *exit_func( void *args )
{
  return NULL;
}
