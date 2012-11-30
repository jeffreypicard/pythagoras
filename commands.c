/*
 * commands.c
 *
 * Code for the commands implemented for pythagoras.
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
