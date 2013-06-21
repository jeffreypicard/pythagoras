# pythagoras version
VERSION = 0.1

# Customize below to fit your needs.

# paths

# includes and libs
INCS =
LIBS = 

# flags
CPPFLAGS = -DVERSION=\"${VERSION}\"
CFLAGS = -g -std=c99 -pedantic -Wall -O3 ${INCS} ${CPPFLAGS}
LDFLAGS = -s ${LIBS}

# compiler and linker
CC = clang
LD = ${CC}
