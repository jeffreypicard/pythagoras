#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT([pythagoras], [0.01])
AM_INIT_AUTOMAKE([-Wall foreign])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

# Checks for programs.
AC_PROG_CC_C99
if test -z "$CC" || test "X$CC" = "Xno"; then
  AC_MSG_ERROR([No suitable C99 compiler found])
fi
AM_PROG_CC_C_O
AC_PROG_RANLIB

AC_CHECK_LIB([m],[sin])

#Open MP
#AC_OPENMP
#CFLAGS="$CFLAGS $OPENMP_CFLAGS"
CFLAGS="-Wall $CFLAGS"

dnl For Fortran support, uncomment (remove "dnl") the following
dnl AC_PROG_F77
dnl if test -z "$F77" || test "X$F77" = "Xno"; then
dnl   AC_MSG_ERROR([No suitable F77 compiler found])
dnl fi

AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

echo ""
echo "                       Configure Summary"
echo "                       ================="
echo ""
echo "Compiling Options:"
echo "------------------"
echo "                     C Compiler: $CC"
echo "                       CPPFLAGS: $CPPFLAGS"
echo "                         CFLAGS: $CFLAGS"
echo "                        LDFLAGS: $LDFLAGS"
echo "                           LIBS: $LIBS"
