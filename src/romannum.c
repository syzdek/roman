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

/* displays usage */
void my_key PARAMS((void));

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

   static char   short_options[] = "kn:r:hvV";
   static struct option long_options[] =
   {
      {"help",		no_argument, 0, 'h'},
      {"key",		no_argument, 0, 'k'},
      {"keys",		no_argument, 0, 'k'},
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
         case 'k':
            my_key();
            free(cnf);
            return(NULL);
         case 'n':
            cnf->num = atol(optarg);
            if (cnf->num < 0)
            {
               fprintf(stderr, "%s: Roman numerals must be positive\n", PROGRAM_NAME);
               fprintf(stderr, "Try `%s --key' for more information.\n", PROGRAM_NAME);
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


/* displays usage */
void my_key(void)
{
   printf("Roman Numerals:\n");
   printf(" Symbol    Value              Name\n");
   printf("   N     0  (zero)          (nullae) *\n");
   printf("   I     1  (one)           (unus)\n");
   printf("   V     5  (five)          (quinque)\n");
   printf("   X    10  (ten)           (decem)\n");
   printf("   L    50  (fifty)         (quinquaginta)\n");
   printf("   C   100  (one hundred)   (centum)\n");
   printf("   D   500  (five hundred)  (quingenti)\n");
   printf("   M  1000  (one thousand)  (mille)\n");
   printf("\n");
   printf("Notes:\n");
   printf("   A bar placed across the top of a Roman Numeral implies that\n");
   printf("   the value shoud be multiplied by 1000.  This utility does not\n");
   printf("   use this notation since there is not an acceptable manner of\n");
   printf("   representing this notation using ASCII characters.\n");
   printf("\n");
   printf("* Non-standard Roman numeral used by St. Bede.\n");
   return;
}


/* displays usage */
void my_usage(void)
{
   printf("Usage: %s [OPTIONS]\n", PROGRAM_NAME);
   printf("  -n number             number to convert to Roman Numeral\n");
   printf("  -r numeral            Roman Numeral to convert to number\n");
   printf("  -k, --key             print Roman Numeral key\n");
   printf("  -h, --help            print this help and exit\n");
   printf("  -V, --version         print version number and exit\n");
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
