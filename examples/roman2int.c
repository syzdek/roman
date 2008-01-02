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
 *  examples/roman2int.c - example usage of roman2int()
 *
 *  Simple Build:
 *     gcc -Wall -c roman2int.c
 *     gcc -Wall -o roman2int roman2int.o
 *
 *  Libtool Build:
 *     libtool --mode=compile gcc -Wall -g -O2 -I../include -c roman2int.c
 *     libtool --mode=link    gcc -Wall -g -O2 -L../lib -o roman2int \
 *             roman2int.o -lroman
 *
 *  Libtool Install:
 *     libtool --mode=install install -c roman2int /usr/local/bin/roman2int
 *
 *  Libtool Clean:
 *     libtool --mode=clean rm -f roman2int.lo roman2int
 *
 *  Usage: roman2int <num> <num> ... <num>
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
      num = roman2int(argv[i]);
      if(num == -1)
         perror("roman2int()");
      else
         printf("%s == %i\n", argv[i], num);
   }

   return(0);
}

/* end of source */
