/*
 *  $Id$
 *
 *  Roman Numeral Conversion API
 *  Copyright (c) 2008 David M. Syzdek <roman-project@syzdek.net>
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
 *  tests/check_int2roman_d.c - tests invalid syntax using D
 */

#include <stdio.h>
#include <string.h>
#include <roman.h>

int main(void);

int main(void)
{
   if (roman2int("ID") != -1)
      return(1);
   if (roman2int("VD") != -1)
      return(1);
   if (roman2int("XD") != -1)
      return(1);
   if (roman2int("DD") != -1)
      return(1);
   if (roman2int("DMD") != -1)
      return(1);
   if (roman2int("CCD") != -1)
      return(1);
   return(0);
}

/* end of source */
