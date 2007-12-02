/*
 *  $Id$
 */
/*
 *  Roman Numeral Conversion API
 *  Copyright (c) 2007 David M. Syzdek <roman-project@syzdek.net>
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
 *  lib/libromain.c - contains base functions for converter formats between
 *                    Latin/Roman Numerals and standard format
 */
#define _ROMAN_LIB_LIBROMAN_C 1
#include "libroman.h"


/* buffer for storing conversions */
char roman_string[ROMAN_BUFF_LEN];

/* buffer for storing Latin time */
char roman_ctime_string[ROMAN_BUFF_LEN];

/* Latin days of the month */
const char * roman_latin_weekday[] =
{
   "dies Solis",
   "dies Lunae",
   "dies Martis",
   "dies Mercurii",
   "dies Lovis",
   "dies Veneris",
   "dies Saturni",
   NULL
};


/* Latin days of the month */
const char * roman_latin_month[] =
{
   "Januarius",
   "Februarius",
   "Martius",
   "Aprilis",
   "Maius",
   "Junius",
   "Julius",
   "Augustus",
   "September",
   "October",
   "Novembris",
   "December",
   NULL
};

/////////////////
//             //
//  Functions  //
//             //
/////////////////

/* determines required dst buffer to decode src_len data block */
ROMAN_F(const char *) long2roman(unsigned num)
{
   unsigned pos;
   unsigned u;
   unsigned dividend;

   /* sets initial values */
   pos = 0;
   memset(roman_string, 0, ROMAN_BUFF_LEN);

   /* checks for nullae */
   if (!(num))
   {
      roman_string[0] = 'N';
      return(roman_string);
   };

   /* calculates thousands */
   dividend = num/1000;
   if (dividend > (ROMAN_BUFF_LEN-1))
   {
      errno = EDOM;
      return(NULL);
   };
   for(u = 0; u < dividend; u++)
      roman_string[pos+u] = 'M';
   num %= 1000;
   pos += u;

   /* calculates hundreds */
   dividend = num/100;
   if (dividend > (ROMAN_BUFF_LEN-1-pos))
   {
      errno = EDOM;
      return(NULL);
   };
   if (dividend == 9)
   {
      roman_string[pos+0] = 'C';
      roman_string[pos+1] = 'M';
      pos += 2;
      dividend = 0;
   };
   if (dividend >= 5)
   {
      roman_string[pos] = 'D';
      dividend -= 5;
      pos++;
   };
   if (dividend == 4)
   {
      roman_string[pos+0] = 'C';
      roman_string[pos+1] = 'D';
      dividend -= 4;
      pos += 2;
   };
   for(u = 0; u < dividend; u++)
      roman_string[pos+u] = 'C';
   pos += u;
   num %= 100;

   /* calculates tens */
   dividend = num/10;
   if (dividend > (ROMAN_BUFF_LEN-1-pos))
   {
      errno = EDOM;
      return(NULL);
   };
   if (dividend == 9)
   {
      roman_string[pos+0] = 'X';
      roman_string[pos+1] = 'C';
      dividend = 0;
      pos += 2;
   };
   if (dividend >= 5)
   {
      roman_string[pos+0] = 'L';
      dividend -= 5;
      pos++;
   };
   if (dividend == 4)
   {
      roman_string[pos+0] = 'X';
      roman_string[pos+1] = 'L';
      pos += 2;
      dividend -= 4;
   };
   for(u = 0; u < dividend; u++)
      roman_string[pos+u] = 'X';
   pos += u;
   num %= 10;

   /* calculates ones */
   dividend = num;
   if (dividend > (ROMAN_BUFF_LEN-1-pos))
   {
      errno = EDOM;
      return(NULL);
   };
   if (dividend == 9)
   {
      roman_string[pos+0] = 'I';
      roman_string[pos+1] = 'X';
      dividend = 0;
      pos += 2;
   };
   if (dividend >= 5)
   {
      roman_string[pos+0] = 'V';
      dividend -= 5;
      pos++;
   };
   if (dividend == 4)
   {
      roman_string[pos+0] = 'I';
      roman_string[pos+1] = 'V';
      pos += 2;
      dividend -= 4;
   };
   for(u = 0; u < dividend; u++)
      roman_string[pos+u] = 'I';

   /* ends function */
   return(roman_string);
}


/* determines required dst buffer to decode src_len data block */
ROMAN_F(int) roman2long(const char * rom)
{
   /* declares local vars */
   int      num;
   unsigned i;
   unsigned len;
   unsigned old;
   unsigned diff;

   /* checks args */
   if (!(rom))
   {
      errno = EINVAL;
      return(0);
   };

   /* sets initial values */
   num  = 0;
   len  = strlen(rom);
   old  = 1000;
   diff = 1000;

   /* loops through characters */
   for(i = 0; i < len; i++)
   {

      switch(rom[i])
      {
         case 'n':
         case 'N':
            if (strlen(rom) > 1)
            {
               errno = EINVAL;
               return(-1);
            };
            return(0);
            break;
         case 'i':
         case 'I':
            old   = diff;
            num  += 1;
            diff  = 1;
            break;
         case 'v':
         case 'V':
            num += 5;
            if ((diff < 5) && (old < 5))
            {
               errno = EINVAL;
               return(-1);
            }
            else if (diff < 5)
               num -= (diff * 2);
            old  = diff;
            diff = 5;
            break;
         case 'x':
         case 'X':
            num += 10;
            if ((diff < 10) && (old < 10))
            {
               errno = EINVAL;
               return(-1);
            }
            else if (diff < 10)
               num -= (diff * 2);
            old  = diff;
            diff = 10;
            break;
         case 'l':
         case 'L':
            num += 50;
            if ((diff < 50) && (old < 50))
            {
               errno = EINVAL;
               return(-1);
            }
            else if (diff < 50)
               num -= (diff * 2);
            old  = diff;
            diff = 50;
            break;
         case 'c':
         case 'C':
            num += 100;
            if ((diff < 100) && (old < 100))
            {
               errno = EINVAL;
               return(-1);
            }
            else if (diff < 100)
               num -= (diff * 2);
            old  = diff;
            diff = 100;
            break;
         case 'd':
         case 'D':
            num += 500;
            if ((diff < 500) && (old < 500))
            {
               errno = EINVAL;
               return(-1);
            }
            else if (diff < 500)
               num -= (diff * 2);
            old  = diff;
            diff = 500;
            break;
         case 'm':
         case 'M':
            num += 1000;
            if ((diff < 1000) && (old < 1000))
            {
               errno = EINVAL;
               return(-1);
            }
            else if (diff < 1000)
               num -= (diff * 2);
            old  = diff;
            diff = 1000;
            break;
         default:
            errno = EINVAL;
            return(-1);
      };
   };

   /* ends function */
   return(num);
}


/* returns string containing the date in Latin */
char * roman_ctime(const time_t * t)
{
   /* declares local vars */
   char         day[ROMAN_BUFF_LEN/4];
   char         hour[ROMAN_BUFF_LEN/4];
   char         min[ROMAN_BUFF_LEN/4];
   char         sec[ROMAN_BUFF_LEN/4];
   char         year[ROMAN_BUFF_LEN/4];
   unsigned     u;
   struct tm  * ts;
   const char * ptr;

   ts = localtime(t);

   /* calculates day of month */
   ptr = long2roman((unsigned) ts->tm_mday);
   for(u = 0; u < strlen(ptr); u++)
   {
      if ( (ptr[u] >= 'A') && (ptr[u] <= 'Z') )
         day[u] = ptr[u] - 'A' + 'a';
      else
         day[u] = ptr[u];
   };
   day[u] = '\0';

   strncpy(hour, long2roman((unsigned) ts->tm_hour), ROMAN_BUFF_LEN/4);
   strncpy(min,  long2roman((unsigned) ts->tm_min),  ROMAN_BUFF_LEN/4);
   strncpy(sec,  long2roman((unsigned) ts->tm_sec),  ROMAN_BUFF_LEN/4);
   strncpy(year, long2roman((unsigned) ts->tm_year + 1900), ROMAN_BUFF_LEN/4);

   snprintf(roman_ctime_string, ROMAN_BUFF_LEN, "%s %s %s %s:%s:%s %s %s\n", 
      roman_latin_weekday[ts->tm_wday], roman_latin_month[ts->tm_mon], day,
      hour, min, sec, ts->tm_zone, year);

   /* ends function */
   return(roman_ctime_string);
}

/* end of source file */
