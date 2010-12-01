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
