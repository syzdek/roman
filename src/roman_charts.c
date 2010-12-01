/*
 *  Roman Numeral Conversion API
 *  Copyright (c) 2007 David M. Syzdek <roman-project@syzdek.net>
 *  Copyright (C) 2010 Bindle Binaries
 *
 *  @BINDLE_BINARIES_BSD_LICENSE_START@
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Bindle Binaries nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 *  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL BINDLE BINARIES BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
 *
 *  @BINDLE_BINARIES_BSD_LICENSE_END@
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
