/*
 *  Roman Numeral Conversion API
 *  Copyright (c) 2008 David M. Syzdek <roman-project@syzdek.net>
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
