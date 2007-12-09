#include <stdio.h>
#include <string.h>
#include <roman.h>

int main(int argc, char * argv[]);

int main(int argc, char * argv[])
{
   int    i;
   int    v;
   char   buff[512];

   v = 0;
   if (argc > 1)
      if (!(strcmp(argv[1], "-v")))
         v = 1;

   for(i = 0; i < 5000; i++)
   {
      if (!(long2roman_r(i, buff, 512)))
      {
         if (v)
         {
            perror("long2roman_r");
            fprintf(stderr, "exiting on %i\n", i);
         };
         return(1);
      };
      if (roman2long(buff) != i)
      {
         if (v)
         {
            perror("long2roman_r");
            fprintf(stderr, "exiting on %i\n", i);
         };
         return(1);
      };
      if (v)
         printf("%5i == %s\n", i, buff);
   };

   return(0);
}
