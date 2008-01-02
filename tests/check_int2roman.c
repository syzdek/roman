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
 *  tests/check_int2roman.c - tests int2roman
 */

#include <stdio.h>
#include <string.h>
#include <roman.h>

int main(int argc, char * argv[]);

int main(int argc, char * argv[])
{
   int    i;
   int    v;
   char   buff[ROMAN_BUFF_LEN];

   v = 0;
   if (argc > 1)
      if (!(strcmp(argv[1], "-v")))
         v = 1;

   for(i = ROMAN_NUMERAL_MIN; i < ROMAN_NUMERAL_MAX; i++)
   {
      if (!(int2roman_r(i, buff, 512)))
      {
         if (v)
         {
            perror("int2roman_r");
            fprintf(stderr, "exiting on %i\n", i);
         };
         return(1);
      };
      if (roman2int(buff) != i)
      {
         if (v)
         {
            perror("int2roman_r");
            fprintf(stderr, "exiting on %i\n", i);
         };
         return(1);
      };
      if (v)
         printf("%5i == %s\n", i, buff);
   };

   return(0);
}

/* end of source */
