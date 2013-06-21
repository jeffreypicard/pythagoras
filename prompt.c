/*
 * prompt.c
 *
 * Prompt for pythagoras
 *
 * Copyright (c) 2012, Jeffrey Picard
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met: 
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *  list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *  this list of conditions and the following disclaimer in the documentation
 *  and/or other materials provided with the distribution. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies, 
 * either expressed or implied, of the FreeBSD Project.
 */
/* Standard headers */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* My headers */
#include "pythagoras.h"

/* Constants */
#define NUM_CMDS 100
#define MAX_CMD_LEN 100
#define DEBUG 0

/* Structs */
struct _cmd_def {
  char cmd[NUM_CMDS][MAX_CMD_LEN];
  int len[NUM_CMDS];
  void* (*funcs[NUM_CMDS])( void* );
  int size;
} typedef cmd_def;

cmd_def cmds = {
  {"help", "exit"},
  {0,0},
  { help_func, exit_func, },
  2
};

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
  int buff_size = MAX_CMD_LEN;
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

int execute_command( cmd_info *cmd )
{
  switch( cmd->i )
  {
    case -1:
      pythagoras_os_cmd( (void *)cmd );
      break;
    case 0:
    case 1:
      if( cmds.funcs[cmd->i]( (void*) cmd ) )
        return 1;
      else
        return 0;
      break;
    default:
      return 0;
  }

  return 1;
}

/*
 * parse_input
 *
 * Takes the user input as a string and attempts to parse it.
 *
 * Returns non-zero code indicating the result.
 * Returns zero on exit.
 */
cmd_info *parse_input( char *input )
{
  char *s = input;
  /* Clear whitespace */
  while( isspace(*s) && *s != '\n' ) s++;
  /* They hit enter and nothing else, do nothing */
  if( *s == '\n' )
    return NULL;

  cmd_info *info = NULL;
  int l = strlen( s );
  int i = 0, j = 0;
  char c = 0;
  char *cmd = NULL;

  while( i < l )
  {
    c = s[i];
    if( ' ' == c || '\n' == c )
      break;
    else
      i++;
  }

  cmd = calloc( i+1, sizeof(char) );
  info = calloc( 1, sizeof(cmd_info) );

  strncpy( cmd, s, i );
  info->args = cmd;

  for( j = 0; j < cmds.size; j++ )
  {
    if( 0 == strcmp( cmds.cmd[j], cmd ) )
    {
      info->i = j;
      return info;
      //info = (cmd_info*) cmds.funcs[j]( (void*) cmd, (void*)s );

      //free( cmd );

      /*This will be NULL only if the exit command was given*/
      //if( !info )
      //  return 0;

      //return 1;
    }
  }
  info->i = -1;
  return info;
  /*printf("pythagoras: '%s': command not found\n", cmd );*/
  //pythagoras_os_cmd( (void *)cmd, (void *)s );

  //free( cmd );
  //return -1;
}

/*
 * parse_delimited_cmds
 *
 * Takes a string of commands (or arguments), a delimiter and pointer
 * to a char** to allocate. parses on the specified delimiter. Returns
 * the number of commands parsed.
 */
int parse_delimited_cmds( char *cmd_str, char delim, char ***cmds )
{
  int l = 1, n = 0, i = 0;
  char *s = cmd_str, *s2 = NULL;

  /* Count number of commands */
  while( *s )
  {
    if( *s == delim )
    {
      l++;
      while( *s == delim ) s++;
    }
    s++;
  }

  /* +1 to ensure the array is terminated by a null pointer */
  *cmds = calloc( l + 1, sizeof(char*) );
  if( !*cmds )
    EXIT_WITH_ERROR("Error: malloc failed in parse_delimited_cmds.\n");

  /* Parse commands and copy them into the array of strings */
  s = cmd_str;
  s2 = cmd_str;
  n = 0;
  while( *s )
  {
    n++; 
    if( *s++ == delim )
    {
      while( *s == delim ) s++;

      (*cmds)[i] = calloc( n, sizeof(char) );
      if( !(*cmds)[i] )
        EXIT_WITH_ERROR("Error: malloc failed in parse_delimited_cmds.\n");
      strncpy( (*cmds)[i], s2, n-1 );
      s2 = s; 
      i++;
      n = 0;
    }
  }
  /* Get the command at the end of the string */
  if( n > 0 && s2[0] != delim && s2[0] != '\n' )
  {
    (*cmds)[i] = calloc( n, sizeof(char) );
    if( !(*cmds)[i] )
      EXIT_WITH_ERROR("Error: malloc failed in parse_delimited_cmds.\n");
    strncpy( (*cmds)[i], s2, n-1 );
  }

  return l;
}

/*
 * print_array_strings
 *
 * Takes an array of strings and the number of strings and prints them.
 *
 */
void print_array_strings( char **arr_s, int n )
{
  int i = 0;
  for( i = 0; i < n; i++ )
    fprintf( stderr, "\t\"%s\"\n", arr_s[i] );
}

/*
 * delete_cmds
 *
 * Takes the char** commands array and free it.
 * Must be NULL terminated.
 */
void delete_cmds( char **cmds )
{
  char **s = cmds;
  while( *s )
    free( *s++ );
  free( cmds );
}
