#
#   $Id$
#
#   Roman Numeral Conversion API
#   Copyright (C) 2007 David M. Syzdek <roman-project@syzdek.net>
#
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program; if not, write to the Free Software
#   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
#
#   configure.in - automate compiling on a unix platform
#

# +-=-=-=-=-=-=-=-=-+
# |                 |
# |  Autoconf Init  |
# |                 |
# +-=-=-=-=-=-=-=-=-+

AC_PREREQ(2.61)

AC_COPYRIGHT([Copyright (c) 2007 David M. Syzdek <roman-project@syzdek.net>.])
AC_REVISION($Revision$)
AC_INIT([Roman Numeral Conversion API],[0.0.2alpha1],[syzdek@users.sourceforge.net],[roman])
AC_SUBST(PACKAGE_COPYRIGHT, ["Copyright (C) 2007 David M. Syzdek."])
AC_DEFINE_UNQUOTED(PACKAGE_COPYRIGHT, ["$PACKAGE_COPYRIGHT"], ["Copyright info"])
AC_SUBST([RELEASE_MONTH],["December 2007"])

# Version Info:
#    Current    -- the current version number of this API
#    Revision   -- the revision of the implementation of the API version
#    Age        -- How many seqential past API versions is supported by
#                  this implementation
# Format => Current:Revision:Age
AC_SUBST(LIB_VERSION_INFO, 1:0:0)

AC_CONFIG_AUX_DIR([gnu])
AC_CONFIG_SRCDIR([.])
#AC_CONFIG_LIBOBJ_DIR(compat)
AC_CONFIG_HEADERS([config.h])

# determines host type
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

# configures for automake
AM_MAINTAINER_MODE
AM_INIT_AUTOMAKE(gnu std-options subdir-objects)

# Compilers                                                       
AC_PROG_CC 
AM_PROG_CC_C_O
AC_PROG_INSTALL

# checks for Unix Variants
AC_AIX
AC_GNU_SOURCE
AC_MINIX
AC_C_BIGENDIAN

# binary locations
AC_PROG_INSTALL
AC_PATH_PROG([SHELL],	sh bash,	[AC_MSG_ERROR([missing "sh"])], [$PATH])
AC_CHECK_TOOLS(AR,	ar gar,		[AC_MSG_ERROR([missing binutil "ar"])])
AC_CHECK_TOOLS(LD,	ld gld,		[AC_MSG_ERROR([missing binutil "ld"])])
AC_CHECK_TOOLS(NM,	nm gnm,		[AC_MSG_ERROR([missing binutil "nm"])])
AC_CHECK_TOOLS(RANLIB,	ranlib granlib,	[AC_MSG_ERROR([missing binutil "ranlib"])])
AC_CHECK_TOOLS(STRIP,	strip gstrip,	[AC_MSG_ERROR([missing binutil "strip"])])

# GNU Libtool Support
AC_LIBTOOL_DLOPEN
AC_DISABLE_FAST_INSTALL
AC_LIBTOOL_WIN32_DLL
AC_PROG_LIBTOOL

# configure options
AC_ROMAN_ENABLE_WARNINGS

# checks host
case "${host_os}" in
   *mingw32*) WINTEST=yes ;;
   *win32*)   WINTEST=yes ;;
   *cygwin*)  WINTEST=yes ;;
esac
AM_CONDITIONAL([WIN32], [test "x${WINTEST}" = "xyes"])


# checks data types
AC_CHECK_MEMBER([struct tm.tm_zone],
		[AC_DEFINE_UNQUOTED(HAVE_STRUCT_TM_TM_ZONE, [1], [have time zone member])],, 
		[#include <time.h>])
AC_CHECK_MEMBER([struct tm.tm_gmtoff],
		[AC_DEFINE_UNQUOTED(HAVE_STRUCT_TM_TM_GMTOFF, [1], [have time zone member])],, 
		[#include <time.h>])


# Creates outputs
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

# Show local config
AC_MSG_NOTICE([ ])
AC_MSG_NOTICE([   Roman Numeral Conversions])
AC_MSG_NOTICE([ ])
AC_MSG_NOTICE([   Use Warnings                  $USE_WARNINGS])
AC_MSG_NOTICE([   Use Strict Warnings           $USE_STRICTWARNINGS])
AC_MSG_NOTICE([ ])
AC_MSG_NOTICE([   run `make all'])
AC_MSG_NOTICE([ ])
