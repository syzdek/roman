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
 *  examples/roman2long.c - example usage of roman2long()
 *
 *  Simple Build:
 *     gcc -Wall -c roman2long.c
 *     gcc -Wall -o roman2long roman2long.o
 *
 *  Libtool Build:
 *     libtool --mode=compile gcc -Wall -g -O2 -I../include -c roman2long.c
 *     libtool --mode=link    gcc -Wall -g -O2 -L../lib -o roman2long \
 *             roman2long.o -lroman
 *
 *  Libtool Install:
 *     libtool --mode=install install -c roman2long /usr/local/bin/roman2long
 *
 *  Libtool Clean:
 *     libtool --mode=clean rm -f roman2long.lo roman2long
 *
 *  Usage: roman2long <num> <num> ... <num>
 */

#include <stdio.h>
#include <roman.h>

int main(int argc, char * argv[]);

int main(int argc, char * argv[])
{
   int i;
   int num;

   for(i = 1; i < argc; i++)
   {
      num = roman2long(argv[i]);
      if(num == -1)
         perror("roman2long()");
      else
         printf("%s == %i\n", argv[i], num);
   }

   return(0);
}

/* end of source */
