m4_define([kiff_major_version], [1])
m4_define([kiff_minor_version], [0])
m4_define([kiff_micro_version], [0])
m4_define([kiff_version],
          [kiff_major_version.kiff_minor_version.kiff_micro_version])
	  
m4_define([libkiff_major_version], [1])
m4_define([libkiff_minor_version], [0])
m4_define([libkiff_micro_version], [0])
m4_define([libkiff_version],
          [libkiff_major_version.libkiff_minor_version.libkiff_micro_version])
	  
AC_INIT(kiff, kiff_version)
AM_INIT_AUTOMAKE(subdir-objects -Wall)

AC_LANG(C)

AC_PROG_CC
AC_PROG_MAKE_SET
AC_PROG_INSTALL
AM_PROG_AR

LT_INIT

PKG_CHECK_MODULES([GTK],
[
	glib-2.0 >= 2.44
	gtk+-3.0 >= 3.14
])

KIFF_MAJOR_VERSION=kiff_major_version
KIFF_MINOR_VERSION=kiff_minor_version
KIFF_MICRO_VERSION=kiff_micro_version
KIFF_VERSION=kiff_version
AC_SUBST(KIFF_MAJOR_VERSION)
AC_SUBST(KIFF_MINOR_VERSION)
AC_SUBST(KIFF_MICRO_VERSION)
AC_SUBST(KIFF_VERSION)

LIBKIFF_MAJOR_VERSION=libkiff_major_version
LIBKIFF_MINOR_VERSION=libkiff_minor_version
LIBKIFF_MICRO_VERSION=libkiff_micro_version
LIBKIFF_VERSION=libkiff_version
AC_SUBST(LIBKIFF_MAJOR_VERSION)
AC_SUBST(LIBKIFF_MINOR_VERSION)
AC_SUBST(LIBKIFF_MICRO_VERSION)
AC_SUBST(LIBKIFF_VERSION)

KIFF_INCLUDE_PATH=`pwd`/include
KIFF_LIB_PATH=`pwd`/out/lib
KIFF_BIN_PATH=`pwd`/out/bin
AC_SUBST(KIFF_INCLUDE_PATH)
AC_SUBST(KIFF_LIB_PATH)
AC_SUBST(KIFF_BIN_PATH)

CFLAGS="-std=c11 -W -Wall -Wfatal-errors"
CPPFLAGS="-I$KIFF_INCLUDE_PATH"
LDFLAGS="-L$KIFF_LIB_PATH"

AC_CANONICAL_HOST
case $host_os in
    linux*)
        # Linux system
        ;;
    *mingw32)
        # MinGW32 system
        ;;
    *)
        AC_MSG_ERROR(Your platform is not currently supported ($host_os))
        ;;
esac

AC_CONFIG_FILES(Makefile libkiff/Makefile app/Makefile)
AC_OUTPUT
