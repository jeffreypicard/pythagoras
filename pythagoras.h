/*
 * pythagoras.h
 *
 * Header file for pythagoras.
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

