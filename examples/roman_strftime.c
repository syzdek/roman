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
 *  examples/roman_strftime.c - example usage of roman_strftime()
 *
 *  Simple Build:
 *     gcc -Wall -c roman_strftime.c
 *     gcc -Wall -o roman_strftime roman_strftime.o
 *
 *  Libtool Build:
 *     libtool --mode=compile gcc -Wall -g -O2 -I../include -c roman_strftime.c
 *     libtool --mode=link    gcc -Wall -g -O2 -L../lib -o roman_strftime \
 *             roman_strftime.o -lroman
 *
 *  Libtool Install:
 *     libtool --mode=install install -c roman_strftime /usr/local/bin/roman_strftime
 *
 *  Libtool Clean:
 *     libtool --mode=clean rm -f roman_strftime.lo roman_strftime
 *
 *  Usage: roman_strftime
 */

#include <time.h>
#include <stdio.h>
#include <roman.h>

int main(void);

int main(void)
{
   time_t      t;
   char        buff[512];
   size_t      len;
   struct tm * tm;

   t = time(NULL);

   tm = localtime(&t);

   len = roman_strftime(buff, 512, "%a %b %e %H:%M:%S %Z %Y", tm);
   if (len)
      printf("%s\n", buff);
   else
      perror("roman_strftime()");

   return(0);
}

/* end of source */
