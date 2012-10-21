/*
 * commands.c
 *
 * Code for the commands implemented for pythagoras.
 *
 * Author: Jeffrey Picard
 */
/* Standard Headers */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>   /* fork(), execvp() */
#include <sys/wait.h> /* wait() */
/* My headers */
#include "pythagoras.h"

#define CMD_ERR_VAL 0xAA
/*
 * pythagoras_os_cmd
 *
 * General function to implement an OS command for pythagoras.
 * Called directly my the individual command functions.
 */
void *pythagoras_os_cmd( void* cmd, void* args )
{
  char *cmd_str = (char*)cmd;
  int pid = 0, status = 0;
  char **cmds = NULL;

#if DEBUG_PARSING
  int num_cmds = 0;
  num_cmds = parse_delimited_cmds( (char*) args, ' ', &cmds );
  print_array_strings( cmds, num_cmds );
#else
  parse_delimited_cmds( (char*) args, ' ', &cmds );
#endif

  pid = fork();

  if( pid == 0 )
  {
    status = execvp( cmd_str, cmds );
    if( status == -1 )
      exit( CMD_ERR_VAL );
  }
  else
  {
    wait( &status );
    if( WIFEXITED(status) && WEXITSTATUS(status) == CMD_ERR_VAL )
      fprintf( stderr, "pythagoras: '%s': command not found\n", (char*)cmd );
  }

  delete_cmds( cmds );

  return (void*)1;

}

/******* Other commands *******/

void *exit_func( void *cmd, void *args )
{
  return NULL;
}

void *help_func( void *cmd, void *args )
{
  fprintf( stdout,"Pythagoras, version 0.01. A Pythagorean adventure!\n"
                  "\nCommands:\n"
                  "help\n"
                  "exit\n"
                  "Most things the OS can execute!\n");

  return (void*)1;
}
