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

/* buffer for storing Latin time */
char roman_ctime_string[ROMAN_BUFF_LEN];

/* buffer for storing conversions */
char roman_string[ROMAN_BUFF_LEN];

/* Latin days of the week */
static const char * roman_var_wday[] =
{
   "Solis",
   "Lunae",
   "Martis",
   "Mercurii",
   "Lovis",
   "Veneris",
   "Saturni",
   NULL
};


/* Latin months of the year */
static const char * roman_var_mon[] =
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

/* encodes Arabic numeral with Roman numerals */
ROMAN_F(const char *) long2roman(signed num)
{
   /* wrap long2roman_r() with library buffer */
   return(long2roman_r(num, roman_string, ROMAN_BUFF_LEN));
}


/* encodes Arabic numeral with Roman numerals using external buffer */
ROMAN_F(const char *) long2roman_r(signed num, char * str, unsigned len)
{
   /* local variables */
   unsigned pos;
   unsigned u;
   unsigned dividend;

   /* sets initial values */
   pos = 0;
   memset(str, 0, len);
   len--;

   /* checks for nullae */
   if (!(num))
   {
      str[0] = 'N';
      return(str);
   };

   /* calculates sign */
   if (num < 0)
   {
      num *= -1;
      if (1 > len)
      {
         errno = EDOM;
         return(NULL);
      };
      str[pos] = '-';
      pos++;
   };

   /* calculates thousands */
   dividend = num/1000;
   if (dividend > (len-1))
   {
      errno = EDOM;
      return(NULL);
   };
   for(u = 0; u < dividend; u++)
      str[pos+u] = 'M';
   num %= 1000;
   pos += u;

   /* calculates hundreds */
   dividend = num/100;
   if (dividend > (len-1-pos))
   {
      errno = EDOM;
      return(NULL);
   };
   if (dividend == 9)
   {
      str[pos+0] = 'C';
      str[pos+1] = 'M';
      pos += 2;
      dividend = 0;
   };
   if (dividend >= 5)
   {
      str[pos] = 'D';
      dividend -= 5;
      pos++;
   };
   if (dividend == 4)
   {
      str[pos+0] = 'C';
      str[pos+1] = 'D';
      dividend -= 4;
      pos += 2;
   };
   for(u = 0; u < dividend; u++)
      str[pos+u] = 'C';
   pos += u;
   num %= 100;

   /* calculates tens */
   dividend = num/10;
   if (dividend > (len-1-pos))
   {
      errno = EDOM;
      return(NULL);
   };
   if (dividend == 9)
   {
      str[pos+0] = 'X';
      str[pos+1] = 'C';
      dividend = 0;
      pos += 2;
   };
   if (dividend >= 5)
   {
      str[pos+0] = 'L';
      dividend -= 5;
      pos++;
   };
   if (dividend == 4)
   {
      str[pos+0] = 'X';
      str[pos+1] = 'L';
      pos += 2;
      dividend -= 4;
   };
   for(u = 0; u < dividend; u++)
      str[pos+u] = 'X';
   pos += u;
   num %= 10;

   /* calculates ones */
   dividend = num;
   if (dividend > (len-1-pos))
   {
      errno = EDOM;
      return(NULL);
   };
   if (dividend == 9)
   {
      str[pos+0] = 'I';
      str[pos+1] = 'X';
      dividend = 0;
      pos += 2;
   };
   if (dividend >= 5)
   {
      str[pos+0] = 'V';
      dividend -= 5;
      pos++;
   };
   if (dividend == 4)
   {
      str[pos+0] = 'I';
      str[pos+1] = 'V';
      pos += 2;
      dividend -= 4;
   };
   for(u = 0; u < dividend; u++)
      str[pos+u] = 'I';

   /* ends function */
   return(str);
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
char * roman_asctime(struct tm * tm)
{
   return(roman_asctime_r(tm, roman_ctime_string, ROMAN_BUFF_LEN));
}


/* returns string containing the date in Latin */
char * roman_asctime_r(struct tm * tm, char * buff, unsigned len)
{
   memset(buff, 0, ROMAN_BUFF_LEN);
   roman_strftime(buff, len, "%c\n", tm);
   return(buff);
}


/* returns string containing the date in Latin */
char * roman_ctime(const time_t * tp)
{
   return(roman_ctime_r(tp, roman_ctime_string, ROMAN_BUFF_LEN));
}


/* returns string containing the date in Latin */
char * roman_ctime_r(const time_t * tp, char * buff, unsigned len)
{
   return(roman_asctime_r(localtime(tp), buff, len));
}


/* returns string containing the date in Latin */
ROMAN_F(size_t) roman_strftime(char * str, unsigned str_len, const char * fmt,
	struct tm * tm)
{
   /* declares local vars */
   unsigned     str_pos;
   unsigned     fmt_pos;
   unsigned     fmt_len;

   /* initialize values */   
   str_len--;	/* always leave room for '\0' */
   str_pos = 0;
   fmt_pos = 0;
   fmt_len = strlen(fmt);

   /* loops through format */
   while((fmt_pos < fmt_len) && (str_pos < str_len))
   {
      if (fmt[fmt_pos] != '%')
      {
         str[str_pos] = fmt[fmt_pos];
         str_pos++;
         fmt_pos++;
         continue;
      };
      switch(fmt[fmt_pos+1])
      {
         case 'c':
            str_pos += roman_strftime_str(&str[str_pos], (str_len-str_pos), "%a %b %e %H:%M:%S %Z %Y", tm);
            break;
         case 'D':
         case 'x':
            str_pos += roman_strftime_str(&str[str_pos], (str_len-str_pos), "%m/%d/%y", tm);
            break;
         case 'F':
            str_pos += roman_strftime_str(&str[str_pos], (str_len-str_pos), "%Y-%m-%d", tm);
            break;
         case 'r':
            str_pos += roman_strftime_str(&str[str_pos], (str_len-str_pos), "%I:%M:%S %p", tm);
            break;
         case 'R':
            str_pos += roman_strftime_str(&str[str_pos], (str_len-str_pos), "%H:%M", tm);
            break;
         case 'X':
            str_pos += roman_strftime_str(&str[str_pos], (str_len-str_pos), "%H:%M:%S", tm);
            break;
         default:
            str_pos += roman_strftime_char(&str[str_pos], (str_len-str_pos), fmt[fmt_pos+1], tm);
            break;
      };
      fmt_pos += 2;
   };
   str[str_pos] = '\0';

   /* ends function */
   return(0);
}


/* returns string containing the date in Latin */
ROMAN_F(size_t) roman_strftime_str(char * str, unsigned str_len, const char * fmt,
	struct tm * tm)
{
   /* declares local vars */
   unsigned     str_pos;
   unsigned     fmt_pos;
   unsigned     fmt_len;

   /* initialize values */   
   str_len--;	/* always leave room for '\0' */
   str_pos = 0;
   fmt_pos = 0;
   fmt_len = strlen(fmt);

   /* loops through format */
   while((fmt_pos < fmt_len) && (str_pos < str_len))
   {
      if (fmt[fmt_pos] != '%')
      {
         str[str_pos] = fmt[fmt_pos];
         str_pos++;
         fmt_pos++;
      } else {
         str_pos += roman_strftime_char(&str[str_pos], (str_len-str_pos), fmt[fmt_pos+1], tm);
         fmt_pos += 2;
      };
   };
   str[str_pos] = '\0';

   /* ends function */
   return(str_pos);
}


/* returns string containing the date in Latin */
size_t roman_strftime_char(char * s, unsigned len, int c,
        struct tm * tm)
{
   /* declares local vars */
   char         buff[ROMAN_BUFF_LEN];
   int          num;
   size_t       pos;
   const char * ptr;

   /* initialize variables */
   memset(buff, 0, ROMAN_BUFF_LEN);
   num = 0;
   pos = 0;
   ptr = "";

   /* expands escape character */
   switch(c)
   {
      /*
       *  The following are defined by SUSv3 strftime() declaration
       *  http://www.unix.org/single_unix_specification/
       */
      /* Replaced by the locale's abbreviated weekday name. [ tm_wday] */
      case 'a':
         if (tm->tm_wday > 6)
            ptr = roman_var_wday[6];
         else
            ptr = roman_var_wday[tm->tm_wday];
         pos = 3;
         break;

      /* Replaced by the locale's full weekday name. [ tm_wday] */
      case 'A':
         if (tm->tm_wday > 6)
            pos = strlen(ptr = roman_var_wday[6]);
         else
            pos = strlen(ptr = roman_var_wday[tm->tm_wday]);
         break;

      /* Equivalent to %b. [ tm_mon] */
      case 'h':

      /* Replaced by the locale's abbreviated month name. [ tm_mon] */
      case 'b':
         if (tm->tm_mon > 11)
            ptr = roman_var_mon[11];
         else
            ptr = roman_var_mon[tm->tm_mon];
         pos = 3;
         break;

      /* Replaced by the locale's full month name. [ tm_mon] */
      case 'B':
         pos = strlen(ptr = roman_var_mon[tm->tm_mon]);
         break;

      /*
       * Replaced by the year divided by 100 and truncated to an integer, as a
       * decimal number [00,99]. [ tm_year]
       */
      case 'C':
         pos = strlen(ptr = long2roman(((tm->tm_year+1900) / 100)));
         break;

      /* Replaced by the day of the month as a decimal number */
      case 'd':
         pos = strlen(ptr = long2roman(tm->tm_mday));
         break;

      /* Replaced by the day of the month as a decimal number */
      case 'e':
         pos = strlen(ptr = long2roman(tm->tm_mday));
         break;

      /* Replaced by the last 2 digits of the week-based year */
      case 'g':
         pos = strlen(ptr = long2roman((tm->tm_year % 100)));
         break;

      /* Replaced by the week-based year as a decimal number */
      case 'G':
         pos = strlen(ptr = long2roman(tm->tm_year));
         break;

      /* Replaced by the hour (24-hour clock) as a decimal number */
      case 'H':
         pos = strlen((ptr = long2roman((tm->tm_hour))));
         break;

      /* Replaced by the hour (12-hour clock) as a decimal number */
      case 'I':
         if (tm->tm_hour > 12)
            pos = strlen(ptr = long2roman((tm->tm_hour - 12)));
         else if (!(tm->tm_hour))
            pos = strlen(ptr = long2roman((12)));
         else
            pos = strlen(ptr = long2roman((tm->tm_hour)));
         break;

      /* Replaced by the day of the year as a decimal number [001,366] */
      case 'j':
         pos = strlen(ptr = long2roman((tm->tm_yday+1)));
         break;

      /* Replaced by the month as a decimal number */
      case 'm':
         pos = strlen(ptr = long2roman(tm->tm_mon+1));
         break;

      /* Replaced by the minute as a decimal number */
      case 'M':
         pos = strlen(ptr = long2roman(tm->tm_min));
         break;

      /* replaced by new line */
      case 'n':
         pos = strlen(ptr = "\n");
         break;

      /* Replaced by the locale's equivalent of either a.m. or p.m. */
      case 'p':
         if (tm->tm_hour > 11)
            pos = strlen(ptr = "PM");
         else
            pos = strlen(ptr = "AM");
         break;
      case 'P':
         if (tm->tm_hour > 11)
            pos = strlen(ptr = "pm");
         else
            pos = strlen(ptr = "am");
         break;

//      /* seconds since Jan 1, 1970 */
//      case 's':
//         pos = strlen(ptr = long2roman(mktime(tm)));
//         break;

      /* Replaced by the second */
      case 'S':
         pos = strlen(ptr = long2roman(tm->tm_sec));
         break;

      /* Replaced by a <tab>. */
      case 't':
         pos = strlen(ptr = "\t");
         break;

      /* replaced by the weekday as a number */
      case 'u':
         if (!(tm->tm_wday))
            pos = strlen(ptr = long2roman(7));
         else
            pos = strlen(ptr = long2roman(tm->tm_wday));
         break;

      /* Replaced by the week number of the year */
//      case 'U':
//         num = (tm->tm_yday - tm->tm_wday + 1)/7;
//         pos = strlen(ptr = long2roman(num));
//         break;

//      /* Replaced by the week number of the year */
//      case 'V':
//         break;

      /* Replaced by the weekday as a decimal number [0,6] */
      case 'w':
         pos = strlen(ptr = long2roman(tm->tm_wday));
         break;

//        /* Replaced by the week number of the year */
//      case 'W':
//         break;

      /* Replaced by the last two digits of the year */
      case 'y':
         pos = strlen(ptr = long2roman((tm->tm_year%100)));
         break;

      /* Replaced by the year as a decimal number */
      case 'Y':
         pos = strlen(ptr = long2roman(tm->tm_year));
         break;

      case 'z':
#ifdef HAVE_STRUCT_TM_TM_GMTOFF
         num = tm->tm_gmtoff / 60;
         pos = strlen(ptr = long2roman(num));
#endif
         break;

      /* Replaced by the timezone name or abbreviation */
      case 'Z':
#ifdef HAVE_STRUCT_TM_TM_ZONE
         pos = strlen(ptr = tm->tm_zone);
#endif
         break;

      default:
         s[0] = c;
         return(1);
   };

   if (pos >= len)
      return(0);
   strncpy(s, ptr, pos);
   return(pos);

   /* ends function */
   return(0);
}

/* end of source file */
