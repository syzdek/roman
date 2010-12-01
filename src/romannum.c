/*
 *  Roman Numeral Conversion API
 *  Copyright (c) 2007, 2008 David M. Syzdek <roman-project@syzdek.net>.
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
 *  @BINDLE_BINARIES_BSD_LICENSE_END@ */
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
   int          optind;
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
MyConfig * my_cmdline PARAMS((int argc, char *argv[], int * errp));

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
   int          x;
   int          y;
   int          err;
   MyConfig   * cnf;

   if (!(cnf = my_cmdline(argc, argv, &err)))
      return(err);

   for(x = cnf->optind; x < argc; x++)
   {
      /* determine type of number */
      cnf->rom = NULL;
      for(y = 0; y < (int) strlen(argv[x]); y++)
         if ( ((argv[x][y] < '0') || (argv[x][y] > '9')) && (argv[x][y] != '-') )
            cnf->rom = argv[x];

      /* converts number */
      if (!(cnf->rom))
         printf("%s\n", int2roman(atol(argv[x])));
      else
         printf("%i\n", roman2int(cnf->rom));
   };

   /* ends function */
   free(cnf);
   return(0);
}


/* parses config */
MyConfig * my_cmdline(int argc, char *argv[], int * errp)
{
   /* declares local vars */
   int        c;
   int        x;
   int        y;
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
   *errp        = 1;
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
            *errp = 0;
            return(NULL);
         case 'c':
            my_roman_numeral_chart();
            free(cnf);
            *errp = 0;
            return(NULL);
         case 'V':
            my_version();
            free(cnf);
            *errp = 0;
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
   if ((optind + 1) > argc)
   {
      fprintf(stderr, "%s: missing required arguments\n", PROGRAM_NAME);
      fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
      free(cnf);
      return(NULL);
   };
   cnf->optind = optind;

   for(x = cnf->optind; x < argc; x++)
   {
      /* determine type of number */
      cnf->rom = NULL;
      for(y = 0; y < (int) strlen(argv[x]); y++)
         if ( ((argv[x][y] < '0') || (argv[x][y] > '9')) && (argv[x][y] != '-') )
            cnf->rom = argv[x];

      /* tests number */
      if (!(cnf->rom))
      {
         if (!(int2roman(atol(argv[x]))))
         {
            fprintf(stderr, "%s: invalid argument `%s'\n", PROGRAM_NAME, argv[x]);
            fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
            free(cnf);
            return(NULL);
         };
      } else {
         if ((roman2int(cnf->rom) == -1))
         {
            fprintf(stderr, "%s: invalid argument `%s'\n", PROGRAM_NAME, argv[x]);
            fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
            free(cnf);
            return(NULL);
         };
      };
   };

   /* ends function */
   return(cnf);
}


/* displays usage */
void my_usage(void)
{
   printf("Usage: %s [OPTIONS] number1 number2 ... numberN\n", PROGRAM_NAME);
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
