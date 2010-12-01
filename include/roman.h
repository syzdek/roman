/*
 *  Roman Numeral Conversion API
 *  Copyright (C) 2007 David M. Syzdek <roman-project@syzdek.net>.
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
 *  include/roman.h - libroman.la header file
 */
#ifndef _ROMAN_H
#define _ROMAN_H 1

///////////////////
//               //
//  Definitions  //
//               //
///////////////////

/*
 * The macros "BEGIN_C_DECLS" and "END_C_DECLS" are taken verbatim
 * from section 7.1 of the Libtool 1.5.14 manual.
 */
/* BEGIN_C_DECLS should be used at the beginning of your declarations,
   so that C++ compilers don't mangle their names. Use END_C_DECLS at
   the end of C declarations. */
#undef BEGIN_C_DECLS
#undef END_C_DECLS
#if defined(__cplusplus) || defined(c_plusplus)
# define BEGIN_C_DECLS  extern "C" {
# define END_C_DECLS    }
#else
# define BEGIN_C_DECLS  /* empty */
# define END_C_DECLS    /* empty */
#endif


/*
 * The macro "PARAMS" is taken verbatim from section 7.1 of the
 * Libtool 1.5.14 manual.
 */
/* PARAMS is a macro used to wrap function prototypes, so that
   compilers that don't understand ANSI C prototypes still work,
   and ANSI C compilers can issue warnings about type mismatches. */
#undef PARAMS
#if defined (__STDC__) || defined (_AIX) \
        || (defined (__mips) && defined (_SYSTYPE_SVR4)) \
        || defined(WIN32) || defined (__cplusplus)
# define PARAMS(protos) protos
#else
# define PARAMS(protos) ()
#endif


/* 
 *  Support for DDL/SO exported functions/variables.
 *  This is loosely taken from:
 *      OpenLDAP include/ldap_cdefs.h
 *      http://www.nedprod.com/programs/gccvisibility.html
 */
#undef ROMAN_F	// used to export functions
#undef ROMAN_V	// used to export variables
#undef ROMAN_L	// used for local functions and variables
#if (defined(_WIN32) || defined(__MINGW32__))
#   ifdef _ROMAN_LIBRARY
#      define ROMAN_F(type)   extern __declspec(dllexport) type
#      define ROMAN_V(type)   extern __declspec(dllexport) type
#      define ROMAN_L(type)   type
#     else
#      define ROMAN_F(type)   extern /* __declspec(dllimport) */ type
#      define ROMAN_V(type)   extern /* __declspec(dllimport) */ type
#      define ROMAN_L(type)   type
#   endif
#  else
#   define ROMAN_F(type)      extern __attribute__ ((visibility("default"))) type
#   define ROMAN_V(type)      extern __attribute__ ((visibility("default"))) type
#   define ROMAN_L(type)      __attribute__ ((visibility("hidden"))) type
#endif


/* length of buffers used by library */
#undef  ROMAN_BUFF_LEN
#define ROMAN_BUFF_LEN		512


/* largest value that can be encoded by library */
#undef ROMAN_NUMERAL_MAX
#define ROMAN_NUMERAL_MAX	5000

/*
 *  smallest value that can be encoded by library
 *
 *  Notes:
 *     ROMAN_NUMERAL_MIN should not be set to a negative number (although the
 *     library can handle negative numbers). This behavior is consistent with
 *     roman2long() which uses a negative number to represent an error. The
 *     library should not decode a string it is incapable of encoding.
 *        --David Syzdek 2007/12/11
 */
#undef ROMAN_NUMERAL_MIN
#define ROMAN_NUMERAL_MIN	0

///////////////
//           //
//  Headers  //
//           //
///////////////

#include <inttypes.h>
#include <time.h>


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
BEGIN_C_DECLS

/* encodes number as a string with Roman numerals */
ROMAN_F(const char *) int2roman PARAMS((int num));

/* encodes number as a string with Roman numerals using external buffer */
ROMAN_F(char *) int2roman_r PARAMS((int num, char * str, size_t len));

/* encodes number as a string with Roman numerals */
ROMAN_F(const char *) long2roman PARAMS((int num))
	__attribute__ ((deprecated));

/* encodes number as a string with Roman numerals using external buffer */
ROMAN_F(char *) long2roman_r PARAMS((int num, char * str, size_t len))
	__attribute__ ((deprecated));

/* converts Roman numeral string to integer */
ROMAN_F(int) roman2int PARAMS((const char * str));

/* converts Roman numeral string to integer */
ROMAN_F(int) roman2long PARAMS((const char * str))
	__attribute__ ((deprecated));

/* encodes broken-out time as Roman numerals and Latin */
ROMAN_F(const char *) roman_asctime PARAMS((const struct tm * tm));

/* encodes broken-out time as Roman numerals and Latin using external buffer */
ROMAN_F(char *) roman_asctime_r PARAMS((const struct tm * tm, char * buff,
	size_t len));

/* encodes time as  Roman numerals and Latin */
ROMAN_F(const char *) roman_ctime PARAMS((const time_t * tp));

/* encodes time as  Roman numerals and Latin using external buffer */
ROMAN_F(char *) roman_ctime_r PARAMS((const time_t * tp, char * buff,
	size_t len));

/* encodes broken-out time as Roman numerals according to format "fmt" */
ROMAN_F(size_t) roman_strftime PARAMS((char * str, size_t str_len,
	const char * fmt, const struct tm * tm));

END_C_DECLS

#endif /* end of header */
