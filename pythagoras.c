/*
 * pythagoras.c
 *
 * Main program.
 *
 * Author: Jeffrey Picard
 */
#include <stdlib.h>
#include <stdio.h>
#include "pythagoras.h"

int main( int argc, char **argv )
{
  int c = 1;
  char *buf = NULL;
  while( c )
  {
    print_prompt();

    buf = get_input( stdin );

    c = parse_input( buf );

    free( buf );
  }

  return 0;
}
