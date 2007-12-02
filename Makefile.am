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
#   @configure_input@
#
#   Makefile.am - automate compiling on a unix platform
#

# Sub directories
SUBDIRS					=
DIST_SUBDIRS				=


# Global flags
AM_LIBS					=
AM_LDADD				= -lroman
AM_LDFLAGS				= -L$(top_builddir)/lib
AM_CFLAGS                               = @CFLAGS_WARNINGS@
AM_CPPFLAGS				= -I$(top_srcdir)/include


# automake targets
bin_PROGRAMS				= src/romannum src/romandate
lib_LTLIBRARIES				= lib/libroman.la
include_HEADERS				= include/roman.h
man_MANS				= \
					  doc/long2roman.3 \
					  doc/roman.1 \
					  doc/roman2long.3


# macros for lib/libroman.la
lib_libroman_la_DEPENDENCIES		= lib/libroman.sym Makefile
lib_libroman_la_CFLAGS			= $(AM_CFLAGS)
lib_libroman_la_LIBADD			= $(AM_LIBS)
lib_libroman_la_LDFLAGS			= \
                                          $(AM_LDFLAGS) \
                                          -rpath '$(libdir)' \
					  -no-undefined
lib_libroman_la_SOURCES			= \
					  $(include_HEADERS) \
					  lib/libroman.c \
					  lib/libroman.h
if WIN32
lib_libroman_la_LDFLAGS			+= -release @PACKAGE_VERSION@
else
lib_libroman_la_LDFLAGS			+= -export-symbols $(srcdir)/lib/libroman.sym
lib_libroman_la_LDFLAGS			+= -version-info @LIB_VERSION_INFO@
endif


# macros for src/romannum
src_romannum_DEPENDENCIES		= $(lib_LTLIBRARIES) Makefile
src_romannum_CPPFLAGS			= -DPROGRAM_NAME="\"romannum\"" $(AM_CPPFLAGS)
src_romannum_CFLAGS			= $(AM_CFLAGS)
src_romannum_LDFLAGS			= $(AM_LDFLAGS)
src_romannum_LDADD			= $(AM_LDADD)
src_romannum_SOURCES			= src/romannum.c $(include_HEADERS)

# macros for src/romandate
src_romandate_DEPENDENCIES		= $(lib_LTLIBRARIES) Makefile
src_romandate_CPPFLAGS			= -DPROGRAM_NAME="\"romandate\"" $(AM_CPPFLAGS)
src_romandate_CFLAGS			= $(AM_CFLAGS)
src_romandate_LDFLAGS			= $(AM_LDFLAGS)
src_romandate_LDADD			= $(AM_LDADD)
src_romandate_SOURCES			= src/romandate.c $(include_HEADERS)


TESTS					=
XFAIL_TESTS				=
EXTRA_DIST				= \
					  doc/long2roman.3.in \
					  doc/roman.1.in \
					  doc/roman2long.3.in \
					  lib/libroman.def \
					  lib/libroman.sym 
CLEANFILES				= \
					  a.out \
					  $(srcdir)/a.out \
					  config.h.in~ \
					  $(srcdir)/config.h.in~ \
					  $(man_MANS) \
					  @PACKAGE_TARNAME@-*.tar.* \
					  @PACKAGE_TARNAME@-*.zip


# substitution routine
do_subst = sed \
	-e 's,[@]SHELL[@],@SHELL@,g' \
	-e 's,[@]PACKAGE_VERSION[@],@PACKAGE_VERSION@,g' \
	-e 's![@]PACKAGE_NAME[@]!@PACKAGE_NAME@!g' \
	-e 's,[@]PACKAGE_TARNAME[@],@PACKAGE_TARNAME@,g' \
	-e 's,[@]PACKAGE_BUGREPORT[@],@PACKAGE_BUGREPORT@,g' \
	-e 's,[@]RELEASE_MONTH[@],@RELEASE_MONTH@,g'


# custom targets
$(man_MANS): Makefile doc/long2roman.3.in doc/roman.1.in doc/roman2long.3.in
	@echo "do_subst < ${@}.in > ${@}"
	@mkdir -p `dirname ${@}` || exit 1
	@${do_subst} < $(srcdir)/${@}.in > ${@} || exit 1
	@chmod 0644 ${@}

# windows dist files
windist: Makefile
	make dist-zip
	make install
	cp @PACKAGE_TARNAME@-@PACKAGE_VERSION@.zip $(DESTDIR)/$(prefix)/
	cp $(srcdir)/ChangeLog                     $(DESTDIR)/$(prefix)/ChangeLog.txt
	cp $(srcdir)/COPYING                       $(DESTDIR)/$(prefix)/COPYING.txt
	cp $(srcdir)/README                        $(DESTDIR)/$(prefix)/README.txt
	cp $(srcdir)/TODO                          $(DESTDIR)/$(prefix)/TODO.txt

# local targets
install-exec-local:

install-data-local: 

uninstall-local:

distclean-local:
	rm -fR $(srcdir)/autom4te.cache

# end of automake file
