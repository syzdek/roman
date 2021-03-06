/*
 *  Roman Numeral Conversion API
 *  Copyright (c) 2007, 2008 David M. Syzdek <roman-project@syzdek.net>
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
 *  tests/check_int2roman.c - tests int2roman
 */

#include <stdio.h>
#include <string.h>
#include <roman.h>

int main(void);

int main(void)
{
   if (roman2int("IC") != -1)
      return(1);
   if (roman2int("XXC") != -1)
      return(1);
   if (roman2int("XCX") != -1)
      return(1);
   if (roman2int("LC") != -1)
      return(1);
   if (roman2int("CLC") != -1)
      return(1);
   if (roman2int("CCLC") != -1)
      return(1);
   if (roman2int("CCVC") != -1)
      return(1);
   if (roman2int("CCIC") != -1)
      return(1);
   if (roman2int("CCCCC") != -1)
      return(1);
   if (roman2int("DCCCCC") != -1)
      return(1);
   return(0);
}

/* end of source */
