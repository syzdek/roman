/*
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
 *  examples/roman_asctime.c - example usage of roman_asctime()
 *
 *  Simple Build:
 *     gcc -Wall -c roman_asctime.c
 *     gcc -Wall -o roman_asctime roman_asctime.o
 *
 *  Libtool Build:
 *     libtool --mode=compile gcc -Wall -g -O2 -I../include -c roman_asctime.c
 *     libtool --mode=link    gcc -Wall -g -O2 -L../lib -o roman_asctime \
 *             roman_asctime.o -lroman
 *
 *  Libtool Install:
 *     libtool --mode=install install -c roman_asctime /usr/local/bin/roman_asctime
 *
 *  Libtool Clean:
 *     libtool --mode=clean rm -f roman_asctime.lo roman_asctime
 *
 *  Usage: roman_asctime 
 */

#include <time.h>
#include <stdio.h>
#include <roman.h>

int main(void);

int main(void)
{
   char         str[512];
   time_t       t;
   struct tm  * tm;
   const char * ptr;

   t = time(NULL);

   tm = localtime(&t);

   ptr = roman_asctime(tm);
   printf("roman_asctime(): %s\n", ptr);

   ptr = roman_asctime_r(tm, str, 512);
   if (!(ptr))
      perror("roman_asctime_r");
   else
      printf("roman_asctime_r(): %s\n", ptr);

   return(0);
}

/* end of source */
