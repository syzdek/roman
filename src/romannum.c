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

/* displays Roman Numeral chart */
void my_chart PARAMS((void));

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
      if ((num = roman2long(cnf->rom)) == -1)
      {
         perror(PROGRAM_NAME ": roman2long()");
         free(cnf);
         return(1);
      };
      printf("%u\n", num);
   }
   else if (cnf->num != -1)
   {
      if (!(str = long2roman((unsigned) cnf->num)))
      {
         perror(PROGRAM_NAME ": long2roman()");
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
   int        c;
   int        option_index;
   MyConfig * cnf;

   static char   short_options[] = "cd:r:hvV";
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
            my_chart();
            free(cnf);
            return(NULL);
         case 'd':
            cnf->num = atol(optarg);
            if (cnf->num < 0)
            {
               fprintf(stderr, "%s: Roman numerals must be positive\n", PROGRAM_NAME);
               fprintf(stderr, "Try `%s --chart' for more information.\n", PROGRAM_NAME);
               free(cnf);
               return(NULL);
            };
            break;
         case 'r':
            cnf->rom = optarg;
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

   /* checks arguments */
   if ( (cnf->rom) && (cnf->num != -1) )
   {
      fprintf(stderr, "%s: incompatible arguments `-r' and `-n'\n", PROGRAM_NAME);
      fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
      free(cnf);
      return(NULL);
   };
   if ( (!(cnf->rom)) && (cnf->num == -1) )
   {
      fprintf(stderr, "%s: missing required arguments\n", PROGRAM_NAME);
      fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
      free(cnf);
      return(NULL);
   };

   /* ends function */
   return(cnf);
}


/* displays Roman Numeral chart */
void my_chart(void)
{
   int i;
   const char ** chart;
   chart = roman_chart();
   for(i = 0; chart[i]; i++)
      printf("%s\n", chart[i]);
   return;
}


/* displays usage */
void my_usage(void)
{
   printf("Usage: %s [OPTIONS]\n", PROGRAM_NAME);
   printf("  -d number                 number to convert to Roman Numeral\n");
   printf("  -r numeral                Roman Numeral to convert to number\n");
   printf("  -c, --chart               print this help and exit\n");
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
