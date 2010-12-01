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
 *
 *  tests/check_roman2int.c - tests roman2long
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
