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
 *  tests/check_int2roman_i.c - tests invalid syntax using I
 */

#include <stdio.h>
#include <string.h>
#include <roman.h>

int main(void);

int main(void)
{
   if (roman2int("NN") != -1)
      return(1);
   if (roman2int("NI") != -1)
      return(1);
   if (roman2int("NV") != -1)
      return(1);
   if (roman2int("NX") != -1)
      return(1);
   if (roman2int("NL") != -1)
      return(1);
   if (roman2int("NC") != -1)
      return(1);
   if (roman2int("ND") != -1)
      return(1);
   if (roman2int("NM") != -1)
      return(1);
   if (roman2int("IN") != -1)
      return(1);
   if (roman2int("VN") != -1)
      return(1);
   if (roman2int("XN") != -1)
      return(1);
   if (roman2int("LN") != -1)
      return(1);
   if (roman2int("CN") != -1)
      return(1);
   if (roman2int("DN") != -1)
      return(1);
   if (roman2int("MN") != -1)
      return(1);
   return(0);
}

/* end of source */
