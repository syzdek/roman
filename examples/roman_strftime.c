/*
 *  $Id$
 *
 *  Roman Numeral Conversion API
 *  Copyright (c) 2007 David M. Syzdek <roman-project@syzdek.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 *  examples/roman_strftime.c - example usage of roman_strftime()
 *
 *  Simple Build:
 *     gcc -Wall -c roman_strftime.c
 *     gcc -Wall -o roman_strftime roman_strftime.o
 *
 *  Libtool Build:
 *     libtool --mode=compile gcc -Wall -g -O2 -I../include -c roman_strftime.c
 *     libtool --mode=link    gcc -Wall -g -O2 -L../lib -o roman_strftime \
 *             roman_strftime.o -lroman
 *
 *  Libtool Install:
 *     libtool --mode=install install -c roman_strftime /usr/local/bin/roman_strftime
 *
 *  Libtool Clean:
 *     libtool --mode=clean rm -f roman_strftime.lo roman_strftime
 *
 *  Usage: roman_strftime
 */

#include <time.h>
#include <stdio.h>
#include <roman.h>

int main(void);

int main(void)
{
   time_t      t;
   char        buff[512];
   size_t      len;
   struct tm * tm;

   t = time(NULL);

   tm = localtime(&t);

   len = roman_strftime(buff, 512, "%a %b %e %H:%M:%S %Z %Y", tm);
   if (len)
      printf("%s\n", buff);
   else
      perror("roman_strftime()");

   return(0);
}

/* end of source */
