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
 *  examples/long2roman.c - example usage of long2roman()
 *
 *  Simple Build:
 *     gcc -Wall -c long2roman.c
 *     gcc -Wall -o long2roman long2roman.o
 *
 *  Libtool Build:
 *     libtool --mode=compile gcc -Wall -g -O2 -I../include -c long2roman.c
 *     libtool --mode=link    gcc -Wall -g -O2 -L../lib -o long2roman \
 *             long2roman.o -lroman
 *
 *  Libtool Install:
 *     libtool --mode=install install -c long2roman /usr/local/bin/long2roman
 *
 *  Libtool Clean:
 *     libtool --mode=clean rm -f long2roman.lo long2roman
 *
 *  Usage: long2roman <num> <num> ... <num>
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <roman.h>

int main(int argc, char * argv[]);

int main(int argc, char * argv[])
{
   int          i;
   int          num;
   char         buff[512];
   const char * ptr;

   for(i = 1; i < argc; i++)
   {
      num = atol(argv[i]);

      ptr = long2roman(num);
      if(ptr)
         printf("long2roman() %i == %s\n", num, ptr);
      else
         perror("long2roman_r()");

      ptr = long2roman_r(num, buff, 512);
      if(ptr)
         printf("long2roman_r() %i == %s\n", num, ptr);
      else
         perror("long2roman_r()");
   }

   return(0);
}

/* end of source code */
