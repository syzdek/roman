/*
 *  Roman Numeral Conversion API
 *  Copyright (c) 2007, 2008 David M. Syzdek <roman-project@syzdek.net>
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
 *  tests/check_int2roman_x.c - tests invalid syntax using X
 */

#include <stdio.h>
#include <string.h>
#include <roman.h>

int main(void);

int main(void)
{
   if (roman2int("IIX") != -1)
      return(1);
   if (roman2int("IXI") != -1)
      return(1);
   if (roman2int("VX") != -1)
      return(1);
   if (roman2int("XVX") != -1)
      return(1);
   if (roman2int("XXVX") != -1)
      return(1);
   if (roman2int("XXXXX") != -1)
      return(1);
   if (roman2int("VXXXXX") != -1)
      return(1);
   if (roman2int("CXXXXX") != -1)
      return(1);
   return(0);
}

/* end of source */
