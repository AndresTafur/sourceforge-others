AC_INIT(whitehawkAv, 0.4,darkhawk665@yahoo.com)
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_SRCDIR(src)
AC_CONFIG_MACRO_DIR([m4])
AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE(whitehawkAv,0.4)

AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_LIBTOOL_DLOPEN
AC_GNU_SOURCE
AM_GNU_GETTEXT([external])

AM_PROG_LEX
AC_PROG_LIBTOOL
AC_STDC_HEADERS

abs_srcdir="`cd $srcdir && pwd`"
CPPFLAGS=" $CPPFLAGS -I$abs_srcdir/include "

dnl
dnl GCC specifics
dnl
AC_MSG_CHECKING([for gcc/g++])
if test "$GXX" = "yes" ; then
   AC_MSG_RESULT([found (using "-Wall" and "-fexceptions")])
   CPPFLAGS="$CPPFLAGS -Wall -fexceptions "
   CXXFLAGS="$CXXFLAGS -Wall -fexceptions"
else
   AC_MSG_RESULT([non gcc/g++ compiler])
fi

dnl
dnl clamAV
dnl

CLAM_CONFIGS="clamav-config"
AC_ARG_WITH(clamav-config,
[[  --with-clamav-config=FILE     Use the given path to wx-config when determining
                            wxWidgets configuration; defaults to "wx-config"]],
[
    if test "$withval" != "yes" -a "$withval" != ""; then
        CLAM_CONFIGS=$withval
    fi
])
AC_MSG_CHECKING([clamav version])
CLAM_CONFIG=""
for VALUE in $CLAM_CONFIGS ; do
	if CLAM_VERSION=`$VALUE --version 2>&1` ; then
		CLAM_CONFIG=$VALUE
		break
	fi
done
if test $CLAM_CONFIG ; then	
	AC_MSG_RESULT([$CLAM_VERSION])
else
	AC_MSG_RESULT([not found])
	AC_MSG_ERROR([Clamav is required. Try --with-clamav-config.])
fi
case $CLAM_VERSION in
    [0.95.[1-9]])
     ;;
    *)
        AC_MSG_ERROR([clamav >= 0.95.1 required, found version $CLAM_VERSION])
        ;;
esac


CPPFLAGS="$CPPFLAGS `$CLAM_CONFIG --cflags`"
CXXFLAGS="$CXXFLAGS `$CLAM_CONFIG --cflags | sed -e 's/-fno-exceptions//'`"
CLAM_LIBS="`$CLAM_CONFIG --libs`"


dnl
dnl wxWidgets
dnl

WX_CONFIGS="wx-config"
AC_ARG_WITH(wx-config,
[[  --with-wx-config=FILE     Use the given path to wx-config when determining
                            wxWidgets configuration; defaults to "wx-config"]],
[
    if test "$withval" != "yes" -a "$withval" != ""; then
        WX_CONFIGS=$withval
    fi
])
AC_MSG_CHECKING([wxWidgets version])
WX_CONFIG=""
for VALUE in $WX_CONFIGS ; do
	if WX_VERSION=`$VALUE --version 2>&1` ; then
		WX_CONFIG=$VALUE
		break
	fi
done
if test $WX_CONFIG ; then	
	AC_MSG_RESULT([$WX_VERSION])
else
	AC_MSG_RESULT([not found])
	AC_MSG_ERROR([wxWidgets is required. Try --with-wx-config.])
fi
case $WX_VERSION in
    [2.4.[2-9]])
        ;;
    [2.[5-9].*])
	;;
    *)
        AC_MSG_ERROR([wxWidgets >= 2.4.2 required, found version $WX_VERSION])
	AC_MSG_ERROR([Try --with-wx-config.])
        ;;
esac
CPPFLAGS="$CPPFLAGS `$WX_CONFIG --cppflags`"
CXXFLAGS="$CXXFLAGS `$WX_CONFIG --cxxflags | sed -e 's/-fno-exceptions//'`"
WX_LIBS="`$WX_CONFIG --libs`"



dnl
dnl whitehawk
dnl

WH_CONFIGS="pkg-config whutil-1.0"
AC_MSG_CHECKING([libwhutil version])
WH_CONFIG="pkg-config whutil-1.0"
for VALUE in $WH_CONFIGS ; do
	if WH_VERSION=`$VALUE --version 2>&1` ; then
		WH_CONFIG=$VALUE
		break
	fi
done
if test $WH_CONFIG ; then	
	AC_MSG_RESULT([$WH_VERSION])
else
	AC_MSG_RESULT([not found])
	AC_MSG_ERROR([libwhutil is required.])
fi

case $WH_VERSION in
    [0.22])
     ;;
    *)
        AC_MSG_ERROR([whutil >= 0.22 required, found version $WH_VERSION])
        ;;
esac


CPPFLAGS="$CPPFLAGS `$WH_CONFIG whutil-1.0 --cflags`"
CXXFLAGS="$CXXFLAGS `$WH_CONFIG whutil-1.0 --cflags`"
WH_LIBS="`$WH_CONFIG whutil-1.0 --libs`"


AC_SUBST(WX_LIBS)
AC_SUBST(WH_LIBS)
AC_SUBST(CLAM_LIBS)
AC_OUTPUT(Makefile src/Makefile data/Makefile po/Makefile.in)
