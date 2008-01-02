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
 *  src/romannum.c - utility for convertingi to/from Roman Numerals
 */
/*
 *  Simple Build:
 *     gcc -Wall -c romannum.c
 *     gcc -Wall -c roman_charts.c
 *     gcc -Wall -o romannum romannum.o roman_charts.o
 *
 *  Libtool Build:
 *     libtool --mode=compile gcc -Wall -g -O2 -I../include -c romannum.c
 *     libtool --mode=compile gcc -Wall -g -O2 -I../include -c roman_charts.c
 *     libtool --mode=link    gcc -Wall -g -O2 -L../lib -o romannum \
 *             romannum.o roman_charts.o -lroman
 *
 *  Libtool Install:
 *     libtool --mode=install install -c romannum /usr/local/bin/romannum
 *
 *  Libtool Clean:
 *     libtool --mode=clean rm -f romannum.lo roman_charts.lo romannum
 */
#define _ROMAN_SRC_ROMANNUM_C 1

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

#include <roman.h>

#include "roman_charts.h"

/////////////////
//             //
//  Datatypes  //
//             //
/////////////////

typedef struct my_config_struct
{
   int          opts;
   int          num;
   const char * rom;
} MyConfig;


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////

/* main statement */
int main PARAMS((int argc, char * argv[]));

/* parses config */
MyConfig * my_cmdline PARAMS((int argc, char *argv[]));

/* displays usage */
void my_usage PARAMS((void));

/* displays version */
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
   int          num;
   MyConfig   * cnf;
   const char * str;

   if (!(cnf = my_cmdline(argc, argv)))
      return(1);

   /* converts roman numeral */
   if (cnf->rom)
   {
      if ((num = roman2int(cnf->rom)) == -1)
      {
         perror(PROGRAM_NAME ": roman2int()");
         free(cnf);
         return(1);
      };
      printf("%u\n", num);
   }
   else if (cnf->num != -1)
   {
      if (!(str = int2roman(cnf->num)))
      {
         perror(PROGRAM_NAME ": int2roman()");
         free(cnf);
         return(1);
      };
      printf("%s\n", str);
   };

   /* ends function */
   free(cnf);
   return(0);
}


/* parses config */
MyConfig * my_cmdline(int argc, char *argv[])
{
   /* declares local vars */
   int        i;
   int        c;
   int        option_index;
   MyConfig * cnf;

   static char   short_options[] = "chvV";
   static struct option long_options[] =
   {
      {"help",		no_argument, 0, 'h'},
      {"chart",		no_argument, 0, 'c'},
      {"verbose",	no_argument, 0, 'v'},
      {"version",	no_argument, 0, 'V'},
      {NULL,            0,           0, 0  }
   };

   /* allocates memory */
   if (!(cnf = (MyConfig *) malloc(sizeof(MyConfig))))
   {
      fprintf(stderr, "out of virtual memory\n");
      return(NULL);
   };
   memset(cnf, 0, sizeof(MyConfig));
   cnf->num = -1;

   /* sets variables */
   option_index = 0;

   /* loops through args */
   while((c = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1)
   {
      switch(c)
      {
         case -1:       /* no more arguments */
         case 0:        /* long option toggles */
            break;
         case 'h':
            my_usage();
            free(cnf);
            return(NULL);
         case 'c':
            my_roman_numeral_chart();
            free(cnf);
            return(NULL);
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

   /* checks for number to convert */
   if ((optind + 1) != argc)
   {
      fprintf(stderr, "%s: missing required arguments\n", PROGRAM_NAME);
      fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
      free(cnf);
      return(NULL);
   };

   /* determine type of number */
   for(i = 0; i < (int) strlen(argv[optind]); i++)
      if ( ((argv[optind][i] < '0') || (argv[optind][i] > '9')) && (argv[optind][i] != '-') )
         cnf->rom = argv[optind];

   /* assume the number is arabic if string contains only */
   if (!(cnf->rom))
   {
      cnf->num = atol(argv[optind]);
      if (cnf->num < 0)
      {
         fprintf(stderr, "%s: Roman numerals must be positive\n", PROGRAM_NAME);
         fprintf(stderr, "Try `%s --chart' for more information.\n", PROGRAM_NAME);
         free(cnf);
         return(NULL);
      };
   };

   /* ends function */
   return(cnf);
}


/* displays usage */
void my_usage(void)
{
   printf("Usage: %s [OPTIONS] number\n", PROGRAM_NAME);
   printf("  -c, --chart               print table of the Roman numeral symbols and exit\n");
   printf("  -h, --help                print this help and exit\n");
   printf("  -V, --version             print version number and exit\n");
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
