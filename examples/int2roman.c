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
 *  examples/int2roman.c - example usage of int2roman()
 *
 *  Simple Build:
 *     gcc -Wall -c int2roman.c
 *     gcc -Wall -o int2roman int2roman.o
 *
 *  Libtool Build:
 *     libtool --mode=compile gcc -Wall -g -O2 -I../include -c int2roman.c
 *     libtool --mode=link    gcc -Wall -g -O2 -L../lib -o int2roman \
 *             int2roman.o -lroman
 *
 *  Libtool Install:
 *     libtool --mode=install install -c int2roman /usr/local/bin/int2roman
 *
 *  Libtool Clean:
 *     libtool --mode=clean rm -f int2roman.lo int2roman
 *
 *  Usage: int2roman <num> <num> ... <num>
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

      ptr = int2roman(num);
      if(ptr)
         printf("int2roman() %i == %s\n", num, ptr);
      else
         perror("int2roman_r()");

      ptr = int2roman_r(num, buff, 512);
      if(ptr)
         printf("int2roman_r() %i == %s\n", num, ptr);
      else
         perror("int2roman_r()");
   }

   return(0);
}

/* end of source code */
