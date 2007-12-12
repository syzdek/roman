/*
 *  $Id$
 */
/*
 *  Roman Numeral Conversion API
 *  Copyright (C) 2007 David M. Syzdek <roman-project@syzdek.net>.
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
 * Support for DDL/SO exported functions/variables.
 */
#undef ROMAN_F
#undef ROMAN_V
#if (defined(_WIN32) || defined(__MINGW32__) )
#   ifdef _ROMAN_LIBRARY
#      define ROMAN_F(type)   extern __declspec(dllexport) type
#      define ROMAN_V(type)   extern __declspec(dllexport) type
#     else
#      define ROMAN_F(type)   extern /* __declspec(dllimport) */ type
#      define ROMAN_V(type)   extern /* __declspec(dllimport) */ type
#   endif
#  else
#   define ROMAN_F(type)      extern type
#   define ROMAN_V(type)      extern type
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
ROMAN_F(const char *) long2roman PARAMS((int num));

/* encodes number as a string with Roman numerals using external buffer */
ROMAN_F(char *) long2roman_r PARAMS((int num, char * str, size_t len));

/* converts Roman numeral string to integer */
ROMAN_F(int) roman2long PARAMS((const char * str));

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
