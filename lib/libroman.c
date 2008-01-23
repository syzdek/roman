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

/* internal buffer used by roman_asctime() */
static char roman_var_asctime[ROMAN_BUFF_LEN];

/* internal buffer used by roman_ctime() */
static char roman_var_ctime[ROMAN_BUFF_LEN];

/* internal buffer used by int2roman() */
static char roman_var_int2roman[ROMAN_BUFF_LEN];

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

/* encodes number as a string with Roman numerals */
ROMAN_F(const char *) int2roman(int num)
{
   /* wrap int2roman_r() with library buffer */
   return(int2roman_r(num, roman_var_int2roman, ROMAN_BUFF_LEN));
}


/* encodes number as a string with Roman numerals using external buffer */
ROMAN_F(char *) int2roman_r(int num, char * str, size_t len)
{
   /* local variables */
   unsigned pos;
   unsigned u;
   unsigned dividend;

   /* checks arguments */
   if (! str)
   {
      errno = EFAULT;
      return(NULL);
   };

   /* verify that number is withing boundaries */
   if ((num > ROMAN_NUMERAL_MAX) || (num < ROMAN_NUMERAL_MIN))
   {
      errno = EDOM;
      return(NULL);
   };

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
         errno = ENOBUFS;
         return(NULL);
      };
      str[pos] = '-';
      pos++;
   };

   /* calculates thousands */
   dividend = num/1000;
   if (dividend > (len-1))
   {
      errno = ENOBUFS;
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
      errno = ENOBUFS;
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
      errno = ENOBUFS;
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
      errno = ENOBUFS;
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


/* deprecated in v0.0.4 in favor of int2roman */
/* encodes number as a string with Roman numerals */
ROMAN_F(const char *) long2roman(int num)
{
   /* wrap int2roman_r() with library buffer */
   return(int2roman_r(num, roman_var_int2roman, ROMAN_BUFF_LEN));
}


/* deprecated in v0.0.4 in favor of int2roman_r */
/* encodes number as a string with Roman numerals using external buffer */
ROMAN_F(char *) long2roman_r(int num, char * str, size_t len)
{
   /* wrap int2roman_r() with library buffer */
   return(int2roman_r(num, str, len));
}


/* converts Roman numeral string to integer */
ROMAN_F(int) roman2int(const char * str)
{
   /* declares local vars */
   int      num;
   unsigned i;
   unsigned len;
   unsigned p[2];	// stores values of previous symbols for error checking

   /* checks args */
   if (!(str))
   {
      errno = EFAULT;
      return(0);
   };

   /* sets initial values */
   num  = 0;
   len  = strlen(str);
   p[0] = 1000;
   p[1] = 1000;

   /* loops through characters */
   for(i = 0; i < len; i++)
   {
      switch(str[i])
      {
         case 'n':
         case 'N':
            if (strlen(str) > 1)
            {
               errno = EINVAL;
               return(-1);
            };
            return(0);
            break;
         case 'i':
         case 'I':
            num  += 1;
            /* prevent patterns like IXI */
            if ((p[1] == 1) && (p[0] != 1))
            {
               errno = EINVAL;
               return(-1);
            };

            /* prevent patterns like IIIII and VIIIII */
            if ((!(num%5)) || (!(num%10)))
            {
               errno = EINVAL;
               return(-1);
            };

            p[1]   = p[0];
            p[0]  = 1;
            break;
         case 'v':
         case 'V':
            num += 5;
            if (((p[0] < 5) && (p[1] < 5)) || (p[1] == 5) || (p[0] == 5))
            {
               errno = EINVAL;
               return(-1);
            }
            else if (p[0] < 5)
               num -= (p[0] * 2);
            p[1]  = p[0];
            p[0] = 5;
            break;
         case 'x':
         case 'X':
            num += 10;
            /* prevent patterns like XCX */
            if (((p[0] < 10) && (p[1] < 10)) || ((p[1] < 10) && (p[0] <= 10)))
            {
               errno = EINVAL;
               return(-1);
            };
            if (p[0] == 1)
               num -= (p[0] * 2);
            else if (p[0] < 10)
            {
               errno = EINVAL;
               return(-1);
            };

            /* prevent patterns like XXXXX and VXXXXX */
            if ((!(num%50)) || (!(num%100)))
            {
               errno = EINVAL;
               return(-1);
            };
            p[1]  = p[0];
            p[0] = 10;
            break;
         case 'l':
         case 'L':
            num += 50;
            if (((p[0] < 50) && (p[1] < 50)) || (p[1] == 50) || (p[0] == 50))
            {
               errno = EINVAL;
               return(-1);
            }
            else if (p[0] < 50)
               num -= (p[0] * 2);
            p[1]  = p[0];
            p[0] = 50;
            break;
         case 'c':
         case 'C':
            num += 100;
            /* prevent patterns like CMC */
            if (((p[0] < 100) && (p[1] < 100)) || ((p[1] < 100) && (p[0] <= 100)))
            {
               errno = EINVAL;
               return(-1);
            };
            if (p[0] == 10)
               num -= (p[0] * 2);
            else if (p[0] < 100)
            {
               errno = EINVAL;
               return(-1);
            };

            /* prevent patterns like CCCCC and VCCCCC */
            if ((!(num%500)) || (!(num%1000)))
            {
               errno = EINVAL;
               return(-1);
            };
            p[1]  = p[0];
            p[0] = 100;
            break;
         case 'd':
         case 'D':
            num += 500;
            if (((p[0] < 500) && (p[1] < 500)) || (p[1] == 500) || (p[0] == 500))
            {
               errno = EINVAL;
               return(-1);
            }
            else if (p[0] < 500)
               num -= (p[0] * 2);
            p[1]  = p[0];
            p[0] = 500;
            break;
         case 'm':
         case 'M':
            num += 1000;
            /* prevent patterns like M?M */
            if (((p[0] < 1000) && (p[1] < 1000)) || ((p[1] < 100) && (p[0] <= 1000)))
            {
               errno = EINVAL;
               return(-1);
            };
            if (p[0] == 100)
               num -= (p[0] * 2);
            else if (p[0] < 1000)
            {
               errno = EINVAL;
               return(-1);
            };

            /* prevent patterns like MMMMM and VMMMMM */
            if ((!(num%5000)) || (!(num%10000)))
            {
               errno = EINVAL;
               return(-1);
            };
            p[1]  = p[0];
            p[0] = 1000;
            break;
         default:
            errno = EINVAL;
            return(-1);
      };
   };

   /* ends function */
   return(num);
}


/* converts Roman numeral string to integer */
ROMAN_F(int) roman2long(const char * str)
{
   return(roman2int(str));
}


/* encodes broken-out time as Roman numerals and Latin */
ROMAN_F(const char *) roman_asctime(const struct tm * tm)
{
   return(roman_asctime_r(tm, roman_var_asctime, ROMAN_BUFF_LEN));
}


/* encodes broken-out time as Roman numerals and Latin using external buffer */
ROMAN_F(char *) roman_asctime_r(const struct tm * tm, char * buff, size_t len)
{
   memset(buff, 0, ROMAN_BUFF_LEN);
   roman_strftime(buff, len, "%c\n", tm);
   return(buff);
}


/* encodes time as  Roman numerals and Latin */
ROMAN_F(const char *) roman_ctime(const time_t * tp)
{
   return(roman_ctime_r(tp, roman_var_ctime, ROMAN_BUFF_LEN));
}


/* encodes time as  Roman numerals and Latin using external buffer */
ROMAN_F(char *) roman_ctime_r(const time_t * tp, char * buff, size_t len)
{
   return(roman_asctime_r(localtime(tp), buff, len));
}


/* encodes broken-out time as Roman numerals according to format "fmt" */
ROMAN_F(size_t) roman_strftime(char * str, size_t str_len, const char * fmt,
	const struct tm * tm)
{
   /* declares local vars */
   unsigned     str_add;
   unsigned     str_pos;
   unsigned     fmt_pos;
   unsigned     fmt_len;

   /* checks arguments */
   if ((! str) || (! fmt) || (! tm))
   {
      errno = EFAULT;
      return(0);
   };

   /* initialize values */   
   str_len--;	/* always leave room for '\0' */
   str_add = 0;
   str_pos = 0;
   fmt_pos = 0;
   fmt_len = strlen(fmt);

   /* loops through format */
   while((fmt_pos < fmt_len) && (str_pos < str_len))
   {
      /* handle normal character */
      if (fmt[fmt_pos] != '%')
      {
         str[str_pos] = fmt[fmt_pos];
         str_pos++;
         fmt_pos++;
         continue;
      };

      /* handle format operand */
      switch(fmt[fmt_pos+1])
      {
         case 'c':
            str_add = roman_strftime_str(&str[str_pos], (str_len-str_pos), "%a %b %e %H:%M:%S %Z %Y", tm);
            break;
         case 'D':
         case 'x':
            str_add = roman_strftime_str(&str[str_pos], (str_len-str_pos), "%m/%d/%y", tm);
            break;
         case 'F':
            str_add = roman_strftime_str(&str[str_pos], (str_len-str_pos), "%Y-%m-%d", tm);
            break;
         case 'r':
            str_add = roman_strftime_str(&str[str_pos], (str_len-str_pos), "%I:%M:%S %p", tm);
            break;
         case 'R':
            str_add = roman_strftime_str(&str[str_pos], (str_len-str_pos), "%H:%M", tm);
            break;
         case 'T':
         case 'X':
            str_add = roman_strftime_str(&str[str_pos], (str_len-str_pos), "%H:%M:%S", tm);
            break;
         default:
            str_add = roman_strftime_char(&str[str_pos], (str_len-str_pos), fmt[fmt_pos+1], tm);
            break;
      };
      if (!(str_add))
         return(0);
      str_pos += str_add;
      fmt_pos += 2;
   };

   /* checks length */
   if ((str_pos >= (str_len+1)) || (fmt_pos < fmt_len))
   {
      str[0] = '\0';
      errno  = ENOBUFS;
      return(0);
   };

   /* terminats string */
   str[str_pos] = '\0';

   /* ends function */
   return(str_pos);
}


/* processes a roman_strftime format operand */
ROMAN_L(size_t) roman_strftime_char(char * s, size_t len, int c,
        const struct tm * tm)
{
   /* declares local vars */
   int          i;
   char         buff[ROMAN_BUFF_LEN];
   int          num;
   size_t       pos;
#ifdef HAVE_STRUCT_TM_TM_GMTOFF
   unsigned     u;
#endif
   const char * ptr;

   /* initialize variables */
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

      /* replace with literal '%' */
      case '%':
         pos = strlen(ptr = "%");
         break;

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
         i = (tm->tm_year+1900) / 100;
         pos = strlen(ptr = int2roman_r(i, buff, ROMAN_BUFF_LEN));
         break;

      /* Replaced by the day of the month as a decimal number */
      case 'd':
         pos = strlen(ptr = int2roman_r(tm->tm_mday, buff, ROMAN_BUFF_LEN));
         break;

      /* Replaced by the day of the month as a decimal number */
      case 'e':
         pos = strlen(ptr = int2roman_r(tm->tm_mday, buff, ROMAN_BUFF_LEN));
         break;

      /* Replaced by the last 2 digits of the week-based year */
      case 'g':
         i = tm->tm_year % 100;
         pos = strlen(ptr = int2roman_r(i, buff, ROMAN_BUFF_LEN));
         break;

      /* Replaced by the week-based year as a decimal number */
      case 'G':
         pos = strlen(ptr = int2roman_r(tm->tm_year, buff, ROMAN_BUFF_LEN));
         break;

      /* Replaced by the hour (24-hour clock) as a decimal number */
      case 'H':
         pos = strlen((ptr = int2roman_r(tm->tm_hour, buff, ROMAN_BUFF_LEN)));
         break;

      /* Replaced by the hour (12-hour clock) as a decimal number */
      case 'I':
         if (tm->tm_hour > 12)
            i = tm->tm_hour - 12;
         else if (!(tm->tm_hour))
            i = 12;
         else
            i = tm->tm_hour;
         pos = strlen(ptr = int2roman_r(i, buff, ROMAN_BUFF_LEN));
         break;

      /* Replaced by the day of the year as a decimal number [001,366] */
      case 'j':
         i = tm->tm_yday + 1;
         pos = strlen(ptr = int2roman_r(i, buff, ROMAN_BUFF_LEN));
         break;

      /* Replaced by the month as a decimal number */
      case 'm':
         i = tm->tm_mon + 1;
         pos = strlen(ptr = int2roman_r(i, buff, ROMAN_BUFF_LEN));
         break;

      /* Replaced by the minute as a decimal number */
      case 'M':
         pos = strlen(ptr = int2roman_r(tm->tm_min, buff, ROMAN_BUFF_LEN));
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
//         pos = strlen(ptr = int2roman_r(mktime(tm), buff, ROMAN_BUFF_LEN));
//         break;

      /* Replaced by the second */
      case 'S':
         pos = strlen(ptr = int2roman_r(tm->tm_sec, buff, ROMAN_BUFF_LEN));
         break;

      /* Replaced by a <tab>. */
      case 't':
         pos = strlen(ptr = "\t");
         break;

      /* replaced by the weekday as a number */
      case 'u':
         if (!(tm->tm_wday))
            pos = strlen(ptr = int2roman_r(7, buff, ROMAN_BUFF_LEN));
         else
            pos = strlen(ptr = int2roman_r(tm->tm_wday, buff, ROMAN_BUFF_LEN));
         break;

      /* Replaced by the week number of the year */
//      case 'U':
//         i = (tm->tm_yday - tm->tm_wday + 1)/7;
//         pos = strlen(ptr = int2roman_r(i, buff, ROMAN_BUFF_LEN));
//         break;

//      /* Replaced by the week number of the year */
//      case 'V':
//         break;

      /* Replaced by the weekday as a decimal number [0,6] */
      case 'w':
         pos = strlen(ptr = int2roman_r(tm->tm_wday, buff, ROMAN_BUFF_LEN));
         break;

//        /* Replaced by the week number of the year */
//      case 'W':
//         break;

      /* Replaced by the last two digits of the year */
      case 'y':
         i = tm->tm_year % 100;
         pos = strlen(ptr = int2roman_r(i, buff, ROMAN_BUFF_LEN));
         break;

      /* Replaced by the year as a decimal number */
      case 'Y':
         i = tm->tm_year + 1900;
         pos = strlen(ptr = int2roman_r(i, buff, ROMAN_BUFF_LEN));
         break;

      case 'z':
#ifdef HAVE_STRUCT_TM_TM_GMTOFF
         i = tm->tm_gmtoff / 60;
         if (tm->tm_gmtoff < 0)
            i *= -1;
         pos = strlen(ptr = int2roman_r(i, buff, ROMAN_BUFF_LEN));
         if (tm->tm_gmtoff < 0)
         {
            buff[strlen(buff)+1] = '\0';
            for(u = (unsigned) strlen(buff); u > 0; u--)
               buff[u] = buff[u-1];
            buff[0] = '-';
            pos++;
         };
#else
         pos = strlen(ptr = " ");
#endif
         break;

      /* Replaced by the timezone name or abbreviation */
      case 'Z':
#ifdef HAVE_STRUCT_TM_TM_ZONE
         pos = strlen(ptr = tm->tm_zone);
#else
         pos = strlen(ptr = " ");
#endif
         break;

      default:
         errno = EINVAL;
         return(0);
   };

   /* checks for enough room and copies string */
   if (pos > len)
   {
      errno = ENOBUFS;
      return(0);
   };
   strncpy(s, ptr, pos);

   /* ends function */
   return(pos);
}


/* processes roman_strftime format operand which expands to multiple operands */
ROMAN_L(size_t) roman_strftime_str(char * str, size_t str_len,
        const char * fmt, const struct tm * tm)
{
   /* declares local vars */
   unsigned     str_add;
   unsigned     str_pos;
   unsigned     fmt_pos;
   unsigned     fmt_len;

   /* checks arguments */
   if ((! str) || (! fmt) || (! tm))
   {
      errno = EFAULT;
      return(0);
   };

   /* initialize values */
   str_pos = 0;
   fmt_pos = 0;
   fmt_len = strlen(fmt);

   /* loops through format */
   while((fmt_pos < fmt_len) && (str_pos < str_len))
   {
      if (fmt[fmt_pos] != '%')
      {
         str[str_pos] = fmt[fmt_pos];
         str_add = 1;
         fmt_pos++;
      } else {
         str_add = roman_strftime_char(&str[str_pos], (str_len-str_pos), fmt[fmt_pos+1], tm);
         fmt_pos += 2;
      };
      if (!(str_add))
         return(0);
      str_pos += str_add;
   };

   /* checks for buffer length */
   if ((str_pos > str_len) || (fmt_pos < fmt_len))
   {
      str[0] = '\0';
      errno  = ENOBUFS;
      return(0);
      str[str_pos] = '\0';
   };

   str[str_pos] = '\0';

   /* ends function */
   return(str_pos);
}

/* end of source file */
