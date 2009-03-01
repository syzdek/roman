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
 */
/*
 *  src/roman_charts.c - contains functions that print helpful charts
 */
#define _ROMAN_SRC_ROMAN_CHARTS_C 1
#include "roman_charts.h"

/////////////////
//             //
//  Functions  //
//             //
/////////////////

/* displays chart of Roman numeral values */
void my_roman_numeral_chart(void)
{
   printf("Roman Numerals:\n");
   printf(" Symbol    Value              Name\n");
   printf("   N     0  (zero)          (nullae) *\n");
   printf("   I     1  (one)           (unus)\n");
   printf("   V     5  (five)          (quinque)\n");
   printf("   X    10  (ten)           (decem)\n");
   printf("   L    50  (fifty)         (quinquaginta)\n");
   printf("   C   100  (one hundred)   (centum)\n");
   printf("   D   500  (five hundred)  (quingenti)\n");
   printf("   M  1000  (one thousand)  (mille)\n");
   printf("\n");
   printf("Notes:\n");
   printf("   A bar placed across the top of a Roman Numeral implies that\n");
   printf("   the value shoud be multiplied by 1000.  This utility does not\n");
   printf("   use this notation since there is not an acceptable manner of\n");
   printf("   representing this notation using ASCII characters.\n");
   printf("\n");
   printf("* Non-standard Roman numeral used by St. Bede.\n");
   return;
}


/* end of source file */
