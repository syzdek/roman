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
 *  examples/roman_ctime.c - example usage of roman_ctime()
 *
 *  Simple Build:
 *     gcc -Wall -c roman_ctime.c
 *     gcc -Wall -o roman_ctime roman_ctime.o
 *
 *  Libtool Build:
 *     libtool --mode=compile gcc -Wall -g -O2 -I../include -c roman_ctime.c
 *     libtool --mode=link    gcc -Wall -g -O2 -L../lib -o roman_ctime \
 *             roman_ctime.o -lroman
 *
 *  Libtool Install:
 *     libtool --mode=install install -c roman_ctime /usr/local/bin/roman_ctime
 *
 *  Libtool Clean:
 *     libtool --mode=clean rm -f roman_ctime.lo roman_ctime
 *
 *  Usage: roman_ctime 
 */

#include <time.h>
#include <stdio.h>
#include <roman.h>

int main(void);

int main(void)
{
   char         str[512];
   time_t       t;
   const char * ptr;

   t = time(NULL);

   ptr = roman_ctime(&t);
   printf("roman_ctime(): %s\n", ptr);

   ptr = roman_ctime_r(&t, str, 512);
   if (!(ptr))
      perror("roman_ctime_r");
   else
      printf("roman_ctime_r(): %s\n", ptr);

   return(0);
}

/* end of source */
