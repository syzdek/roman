#
#   Roman Numeral Conversion API
#   Copyright (C) 2007, 2008 David M. Syzdek <roman-project@syzdek.net>
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
AM_LDADD				= lib/libroman.la
AM_LDFLAGS				= -L$(top_builddir)/lib
AM_CFLAGS                               = @CFLAGS_WARNINGS@
AM_CPPFLAGS				= -I$(top_srcdir)/include


# automake targets
bin_PROGRAMS				= src/romannum src/romandate
check_PROGRAMS				= tests/check_int2roman \
					  tests/check_roman2int \
					  tests/check_roman2int_n \
					  tests/check_roman2int_i \
					  tests/check_roman2int_v \
					  tests/check_roman2int_x \
					  tests/check_roman2int_l \
					  tests/check_roman2int_c \
					  tests/check_roman2int_d \
					  tests/check_roman2int_m
noinst_DATA				= lib/libroman.def lib/libroman.sym
lib_LTLIBRARIES				= lib/libroman.la
include_HEADERS				= include/roman.h
man_MANS				= doc/int2roman.3 \
					  doc/int2roman_r.3 \
					  doc/long2roman.3 \
					  doc/long2roman_r.3 \
					  doc/roman.7 \
					  doc/roman2int.3 \
					  doc/roman2long.3 \
					  doc/roman_asctime.3 \
					  doc/roman_asctime_r.3 \
					  doc/roman_ctime.3 \
					  doc/roman_ctime_r.3 \
					  doc/roman_strftime.3 \
					  doc/romandate.1 \
					  doc/romannum.1 \
					  doc/romannumeral.7


# macros for lib/libroman.la
lib_libroman_la_DEPENDENCIES		= lib/libroman.def lib/libroman.sym Makefile
lib_libroman_la_CFLAGS			= $(AM_CFLAGS)
lib_libroman_la_LIBADD			= $(AM_LIBS)
lib_libroman_la_LDFLAGS			= $(AM_LDFLAGS) \
                                          -rpath '$(libdir)'
lib_libroman_la_SOURCES			= $(include_HEADERS) \
					  lib/libroman.c \
					  lib/libroman.h
if WIN32
lib_libroman_la_LDFLAGS			+= -release @LIB_RELEASE_INFO@
lib_libroman_la_LDFLAGS			+= -export-symbols $(builddir)/lib/libroman.def
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
src_romannum_SOURCES			= $(include_HEADERS) \
					  src/roman_charts.c \
					  src/roman_charts.h \
					  src/romannum.c

# macros for src/romandate
src_romandate_DEPENDENCIES		= $(lib_LTLIBRARIES) Makefile
src_romandate_CPPFLAGS			= -DPROGRAM_NAME="\"romandate\"" $(AM_CPPFLAGS)
src_romandate_CFLAGS			= $(AM_CFLAGS)
src_romandate_LDFLAGS			= $(AM_LDFLAGS)
src_romandate_LDADD			= $(AM_LDADD) 
src_romandate_SOURCES			= $(include_HEADERS) \
					  src/roman_charts.c \
					  src/roman_charts.h \
					  src/romandate.c

# macros for tests/int2roman
tests_check_int2roman_DEPENDENCIES	= $(lib_LTLIBRARIES) Makefile
tests_check_int2roman_LDADD		= $(AM_LDADD)

# macros for tests/roman2int
tests_check_roman2int_DEPENDENCIES	= $(lib_LTLIBRARIES) Makefile
tests_check_roman2int_LDADD		= $(AM_LDADD)

# macros for tests/roman2int_n
tests_check_roman2int_n_DEPENDENCIES	= $(lib_LTLIBRARIES) Makefile
tests_check_roman2int_n_LDADD		= $(AM_LDADD)

# macros for tests/roman2int_i
tests_check_roman2int_i_DEPENDENCIES	= $(lib_LTLIBRARIES) Makefile
tests_check_roman2int_i_LDADD		= $(AM_LDADD)

# macros for tests/roman2int_v
tests_check_roman2int_v_DEPENDENCIES	= $(lib_LTLIBRARIES) Makefile
tests_check_roman2int_v_LDADD		= $(AM_LDADD)

# macros for tests/roman2int_x
tests_check_roman2int_x_DEPENDENCIES	= $(lib_LTLIBRARIES) Makefile
tests_check_roman2int_x_LDADD		= $(AM_LDADD)

# macros for tests/roman2int_l
tests_check_roman2int_l_DEPENDENCIES	= $(lib_LTLIBRARIES) Makefile
tests_check_roman2int_l_LDADD		= $(AM_LDADD)

# macros for tests/roman2int_c
tests_check_roman2int_c_DEPENDENCIES	= $(lib_LTLIBRARIES) Makefile
tests_check_roman2int_c_LDADD		= $(AM_LDADD)

# macros for tests/roman2int_d
tests_check_roman2int_d_DEPENDENCIES	= $(lib_LTLIBRARIES) Makefile
tests_check_roman2int_d_LDADD		= $(AM_LDADD)

# macros for tests/check_roman2int_m
tests_check_roman2int_m_DEPENDENCIES	= $(lib_LTLIBRARIES) Makefile
tests_check_roman2int_m_LDADD		= $(AM_LDADD)


TESTS					= $(check_PROGRAMS)
XFAIL_TESTS				=
EXTRA_DIST				= doc/int2roman.3.in \
					  doc/int2roman_r.3 \
					  doc/long2roman.3 \
					  doc/long2roman_r.3 \
					  doc/roman.7.in \
					  doc/roman2int.3.in \
					  doc/roman2long.3 \
					  doc/roman_asctime.3 \
					  doc/roman_asctime_r.3 \
					  doc/roman_ctime.3.in \
					  doc/roman_ctime_r.3 \
					  doc/roman_strftime.3.in \
					  doc/romandate.1.in \
					  doc/romannum.1.in \
					  doc/romannumeral.7 \
					  examples/int2roman.c \
					  examples/roman2int.c \
					  examples/roman_asctime.c \
					  examples/roman_ctime.c \
					  examples/roman_strftime.c \
					  lib/libroman.def.in \
					  lib/libroman.sym 
CLEANFILES				= \
					  a.out \
					  $(srcdir)/a.out \
					  config.h.in~ \
					  $(srcdir)/config.h.in~ \
					  doc/int2roman.3 \
					  doc/roman.7 \
					  doc/roman2int.3 \
					  doc/roman_ctime.3 \
					  doc/roman_strftime.3 \
					  doc/romandate.1 \
					  doc/romannum.1 \
					  lib/libroman.def \
					  @PACKAGE_TARNAME@-*.tar.* \
					  @PACKAGE_TARNAME@-*.zip


# substitution routine
do_subst = sed \
	-e 's,[@]configure_input[@],${@}. Generated from ${@}.in by make.,g' \
	-e 's,[@]SHELL[@],@SHELL@,g' \
	-e 's,[@]PACKAGE_VERSION[@],@PACKAGE_VERSION@,g' \
	-e 's![@]PACKAGE_NAME[@]!@PACKAGE_NAME@!g' \
	-e 's,[@]PACKAGE_TARNAME[@],@PACKAGE_TARNAME@,g' \
	-e 's,[@]PACKAGE_BUGREPORT[@],@PACKAGE_BUGREPORT@,g' \
	-e 's|[@]PACKAGE_COPYRIGHT[@]|@PACKAGE_COPYRIGHT@|g' \
	-e 's,[@]GIT_PACKAGE_VERSION[@],@GIT_PACKAGE_VERSION@,g' \
	-e 's,[@]RELEASE_MONTH[@],@RELEASE_MONTH@,g'
do_subst_fn = \
		echo "do_subst < ${@}.in > ${@}"; \
		mkdir -p `dirname ${@}` || exit 1; \
		${do_subst} < $(srcdir)/${@}.in > ${@} || exit 1; \
		chmod 0755 ${@}


# custom targets
doc/int2roman.3: Makefile doc/int2roman.3.in
	@$(do_subst_fn)

doc/roman.7: Makefile doc/roman.7.in
	@$(do_subst_fn)

doc/roman2int.3: Makefile doc/roman2int.3.in
	@$(do_subst_fn)

doc/roman_ctime.3: Makefile doc/roman_ctime.3.in
	@$(do_subst_fn)

doc/roman_strftime.3: Makefile doc/roman_strftime.3.in
	@$(do_subst_fn)

doc/romandate.1: Makefile doc/romandate.1.in
	@$(do_subst_fn)

doc/romannum.1: Makefile doc/romannum.1.in
	@$(do_subst_fn)

lib/libroman.def: Makefile lib/libroman.def.in
	@$(do_subst_fn)

htmldocs: Makefile $(man_MANS)
	@$(mkdir_p) doc/html
	groff -Thtml -mandoc doc/int2roman.3      |grep -v 'a href' > doc/html/int2roman.3.html
	groff -Thtml -mandoc doc/roman.7          |grep -v 'a href' > doc/html/roman.7.html
	groff -Thtml -mandoc doc/roman2int.3      |grep -v 'a href' > doc/html/roman2int.3.html
	groff -Thtml -mandoc doc/roman_ctime.3    |grep -v 'a href' > doc/html/roman_ctime.3.html
	groff -Thtml -mandoc doc/roman_strftime.3 |grep -v 'a href' > doc/html/roman_strftime.3.html
	groff -Thtml -mandoc doc/romandate.1      |grep -v 'a href' > doc/html/romandate.1.html
	groff -Thtml -mandoc doc/romannum.1       |grep -v 'a href' > doc/html/romannum.1.html

txtdocs: Makefile $(man_MANS)
	@$(mkdir_p) doc/txt
	groff -a -Tascii -mandoc doc/long2roman.3     |grep -v 'a href' > doc/txt/long2roman.3.txt
	groff -a -Tascii -mandoc doc/roman.7          |grep -v 'a href' > doc/txt/roman.7.txt
	groff -a -Tascii -mandoc doc/roman2long.3     |grep -v 'a href' > doc/txt/roman2long.3.txt
	groff -a -Tascii -mandoc doc/roman_ctime.3    |grep -v 'a href' > doc/txt/roman_ctime.3.txt
	groff -a -Tascii -mandoc doc/roman_strftime.3 |grep -v 'a href' > doc/txt/roman_strftime.3.txt
	groff -a -Tascii -mandoc doc/romandate.1      |grep -v 'a href' > doc/txt/romandate.1.txt
	groff -a -Tascii -mandoc doc/romannum.1       |grep -v 'a href' > doc/txt/romannum.1.txt

#
# Notes for making binary
# windows release.
#
#   RELEASE=x.x.x-win32
#   rm -Rf /tmp/roman-$RELEASE
#
#   ../roman/configure	--prefix=/tmp/roman-$RELEASE --enable-shared \
#			--bindir=/tmp/roman-$RELEASE --host=i386-mingw32
#   make
#   make install
#   make distclean
#   ../roman/configure	--prefix=/tmp/roman-$RELEASE --disable-shared \
#			--bindir=/tmp/roman-$RELEASE --host=i386-mingw32
#   make
#   make windist
#   rm -fR /tmp/roman-$RELEASE/share
#   cd /tmp
#   zip -r roman-$RELEASE.zip roman-$RELEASE
#   
windist: Makefile
	make dist-zip
	make txtdocs
	make install
	cp -R $(builddir)/doc/txt                  $(DESTDIR)/$(prefix)/docs
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
