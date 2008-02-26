/*
 *  $Id$
 */
/*
 *  Roman Numeral Conversion API
 *  Copyright (c) 2007 David M. Syzdek <roman-project@syzdek.net>.
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
 *  src/romandate.c - utility for displaying the date in Latin
 */
/*
 *  Simple Build:
 *     gcc -Wall -c romandate.c
 *     gcc -Wall -c roman_charts.c
 *     gcc -Wall -o romandate romandate.o roman_charts.o
 *
 *  Libtool Build:
 *     libtool --mode=compile gcc -Wall -g -O2 -I../include -c romandate.c
 *     libtool --mode=compile gcc -Wall -g -O2 -I../include -c roman_charts.c
 *     libtool --mode=link    gcc -Wall -g -O2 -L../lib -o romandate \
 *             romandate.o roman_charts.o -lroman
 *
 *  Libtool Install:
 *     libtool --mode=install install -c romandate /usr/local/bin/romandate
 *
 *  Libtool Clean:
 *     libtool --mode=clean rm -f romandate.lo roman_charts.lo romandate
 */
#define _ROMAN_SRC_ROMANDATE_C 1

///////////////
//           //
//  Headers  //
//           //
///////////////

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

#include <time.h>

#include <roman.h>

#include "roman_charts.h"


///////////////////
//               //
//  Definitions  //
//               //
///////////////////

#ifndef PROGRAM_NAME
#define PROGRAM_NAME "romandate"
#endif

#ifndef PACKAGE_NAME
#define PACKAGE_NAME "Roman Numeral Conversion API"
#endif

#ifndef PACKAGE_VERSION
#define PACKAGE_VERSION ""
#endif

#ifndef PACKAGE_COPYRIGHT
#define PACKAGE_COPYRIGHT "Copyright (C) 2007 David M. Syzdek"
#endif

#define MY_BUFF_LEN	1024

#define MY_OPT_UTC	0x0001

/////////////////
//             //
//  Datatypes  //
//             //
/////////////////

typedef struct my_config_struct
{
   int          opts;
   time_t       tclock;
   const char * fmt;
} MyConfig;


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////

/* main statement */
int main PARAMS((int argc, char * argv[]));

/* converts string to time */
time_t my_ascii2time PARAMS((const char * str));

/* parses config */
MyConfig * my_cmdline PARAMS((int argc, char *argv[]));

/* displays usage */
void my_usage PARAMS((void));

/* displays usage */
void my_version PARAMS((void));


/////////////////
//             //
//  Functions  //
//             //
/////////////////

/* main statement */
int main(int argc, char * argv[])
{
   /* declares local vars */
   char         buff[MY_BUFF_LEN];
   MyConfig   * cnf;
   struct tm  * tptr;

   if (!(cnf = my_cmdline(argc, argv)))
      return(1);

   if (cnf->opts & MY_OPT_UTC)
      tptr = gmtime(&cnf->tclock);
   else
      tptr = localtime(&cnf->tclock);

   roman_strftime(buff, MY_BUFF_LEN, &cnf->fmt[1], tptr);

   printf("%s\n", buff);

   /* ends function */
   free(cnf);
   return(0);
}


/* converts string to time using yymmddHHMMSS */
time_t my_ascii2time(const char * str)
{
   /* declares local vars */
   char      buff[5];
   size_t    len;
   struct tm tm;

   /* initializes variables */
   memset(&tm,   0, sizeof(struct tm));
   memset(buff, 0, 5);
   len        = strlen(str);
   tm.tm_mday = 1;

   /* check arguments */
   if (len < 2)
      return(0);
   if (len &0x01)
      return(0);
   if (len > 14)
      return(0);

   /* calculates year */
   if (len < 4)
      return(0);
   strncpy(buff, &str[0], 4);
   tm.tm_year = atol(buff) - 1900;
   memset(buff, 0, 5);

   /* calculates month */
   if (len < 6)
      return(mktime(&tm));
   strncpy(buff, &str[4], 2);
   tm.tm_mon = atol(buff) - 1;

   /* calculates month */
   if (len < 8)
      return(mktime(&tm));
   strncpy(buff, &str[6], 2);
   tm.tm_mday = atol(buff);

   /* calculates month */
   if (len < 10)
      return(mktime(&tm));
   strncpy(buff, &str[8], 2);
   tm.tm_hour = atol(buff);

   /* calculates month */
   if (len < 12)
      return(mktime(&tm));
   strncpy(buff, &str[10], 2);
   tm.tm_min = atol(buff);

   /* ends function */
   return(mktime(&tm));
}


/* parses config */
MyConfig * my_cmdline(int argc, char *argv[])
{
   /* declares local vars */
   int        c;
   int        option_index;
   MyConfig * cnf;

   static char   short_options[] = "cd:huvV";
   static struct option long_options[] =
   {
      {"chart",		no_argument,		0, 'c'},
      {"date",          required_argument,	0, 'd'},
      {"help",		no_argument,		0, 'h'},
      {"utc",		no_argument,		0, 'u'},
      {"universal",	no_argument,		0, 'u'},
      {"verbose",	no_argument,		0, 'v'},
      {"version",	no_argument,		0, 'V'},
      {NULL,		0,			0, 0}
   };

   /* allocates memory */
   if (!(cnf = (MyConfig *) malloc(sizeof(MyConfig))))
   {
      fprintf(stderr, "out of virtual memory\n");
      return(NULL);
   };
   memset(cnf, 0, sizeof(MyConfig));

   /* sets variables */
   option_index = 0;
   cnf->tclock  = time(NULL);

   /* loops through args */
   while((c = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1)
   {
      switch(c)
      {
         case -1:       /* no more arguments */
         case 0:        /* long option toggles */
            break;
         case 'c':
            my_roman_numeral_chart();
            free(cnf);
            return(NULL);
         case 'd':
            if (!(cnf->tclock = my_ascii2time(optarg)))
            {
               fprintf(stderr, "%s: invalid time STRING\n", PROGRAM_NAME);
               fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
               free(cnf);
               return(NULL);
            };
            break;
         case 'h':
            my_usage();
            free(cnf);
            return(NULL);
         case 'u':
            cnf->opts |= MY_OPT_UTC;
            break;
         case 'V':
            my_version();
            free(cnf);
            return(NULL);
         case '?':
            fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
            free(cnf);
            return(NULL);
         default:
            fprintf(stderr, "%s: unrecognized option `--%c'\n", PROGRAM_NAME, c);
            fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
            free(cnf);
            return(NULL);
      };
   };

   /* sets date format string */
   if (optind < argc)
      cnf->fmt = argv[optind];
   else
      cnf->fmt = "+%a %b %e %H:%M:%S %Z %Y";
   if (cnf->fmt[0] != '+')
   {
      fprintf(stderr, "%s: illegal time format\n", PROGRAM_NAME);
      fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
      free(cnf);
      return(NULL);
   };

   /* ends function */
   return(cnf);
}


/* displays usage */
void my_usage(void)
{
   printf("Usage: %s [OPTIONS] [+format]\n", PROGRAM_NAME);
   printf("  -c, --chart               print table of the Roman numeral symbols and exit\n");
   printf("  -d, --date=YYYYmmddHHMMSS display time described by YYYYmmddHHMMSS, not `now'\n");
   printf("  -h, --help                print this help and exit\n");
   printf("  -u, --utc, --universal    print Coordinated Universal Time\n");
   printf("  -V, --version             print version number and exit\n");
   printf("\n");
   printf("Date Format:\n");
   printf("  %%%%   a literal %%\n");
   printf("  %%a   Latin's abbreviated weekday name (Sol..Sat)\n");
   printf("  %%A   Latin's full weekday name, variable length (Solis..Saturni)\n");
   printf("  %%b   Latin's abbreviated month name (Jan..Dec)\n");
   printf("  %%B   Latin's full month name, variable length (Januarius..December)\n");
   printf("  %%c   Latin's date and time (Sat Nov IV XII:II:XXXIII EST MCMXCVII)\n");
   printf("  %%C   century\n");
   printf("  %%d   same as %%e\n");
   printf("  %%D   same as %%m/%%d/%%Y\n");
   printf("  %%e   day of month (I..XXXI)\n");
   printf("  %%F   same as %%Y-%%m-%%d\n");
   printf("  %%g   year of century (N..XCIX)\n");
   printf("  %%G   year\n");
   printf("  %%h   same as %%b\n");
   printf("  %%H   hour using 24-hour notation (N..XXIII)\n");
   printf("  %%I   hour using 12-hour notation (N..XII\n");
   printf("  %%j   day of year (I..XXXLXVI)\n");
   printf("  %%k   hour (0..XXIII)\n");
   printf("  %%l   hour (I..XII)\n");
   printf("  %%m   month (I..XII)\n");
   printf("  %%M   minute (N..LIX)\n");
   printf("  %%n   a newline\n");
   //printf("  %%N   nanoseconds\n");
   printf("  %%p   Latin's upper case AM or PM indicator\n");
   printf("  %%P   Latin's lower case AM or PM indicator\n");
   printf("  %%r   time as %%I:%%M:%%S %%p\n");
   printf("  %%R   time as %%H:%%M\n");
   printf("  %%S   second (I..LX)\n");
   printf("  %%t   a horizontal tab\n");
   printf("  %%T   time as %%H:%%M:%%S\n");
   printf("  %%u   day of week (I..VII);  I represents Lunae\n");
   //printf("  %%U   week number of year with Solis as first day of week\n");
   //printf("  %%V   week number of year with Lunae as first day of week\n");
   printf("  %%w   day of week (N..VI);  N represents Solis\n");
   //printf("  %%W   week number of year with Lunae as first day of week\n");
   printf("  %%x   date as %%m/%%d/%%Y\n");
   printf("  %%X   same as %%T\n");
   printf("  %%y   same as %%g\n");
   printf("  %%Y   same as %%G\n");
   printf("  %%z   GMT offset\n");
   printf("  %%Z   time zone or nothing if no time zone is determinable\n");
#ifdef PACKAGE_BUGREPORT
   printf("\n");
   printf("Report bugs to <%s>.\n", PACKAGE_BUGREPORT);
#endif
   return;
}


/* displays version */
void my_version(void)
{
   printf("%s (%s) %s\n", PROGRAM_NAME, PACKAGE_NAME, PACKAGE_VERSION);
   printf("Written by David M. Syzdek.\n");
   printf("\n");
#ifdef PACKAGE_COPYRIGHT
   printf("%s\n", PACKAGE_COPYRIGHT);
#endif
   printf("This is free software; see the source for copying conditions.  There is NO\n");
   printf("warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n");
   return;
}

/* end of source file */
