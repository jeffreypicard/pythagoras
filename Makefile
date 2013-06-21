# pythagoras - command line text adventure.
# Makefile taken from suckless style.

include config.mk

SRC = pythagoras.c prompt.c commands.c
OBJ = ${SRC:.c=.o}

all: options pythagoras

options:
	@echo pythagoras build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"
	@echo "LD       = ${LD}"

%.o: %.c
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

${OBJ}: config.mk

pythagoras: ${OBJ}
	@echo LD $@
	@${LD} -o $@ ${OBJ} ${LDFLAGS}

clean:
	@echo cleaning
	@rm -f pythagoras ${OBJ} pythagoras-${VERSION}.tar.gz

dist: clean
	@echo creating dist tarball
	@mkdir -p pythagoras-${VERSION}
	@cp -R Makefile LICENSE README.md config.mk ${SRC} pythagoras-${VERSION}
	@tar -cf pythagoras-${VERSION}.tar pythagoras-${VERSION}
	@gzip pythagoras-${VERSION}.tar
	@rm -rf pythagoras-${VERSION}

.PHONY: all options clean dist
