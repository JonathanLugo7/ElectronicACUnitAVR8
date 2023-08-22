/*
 * Common.c
 *
 * Created: 8/7/2016 2:11:55 a. m.
 *  Author: IoT SolucioneX (jlugo)
 */

#include "common.h"


/*
int16_t mapValue16(int16_t value, int16_t minIn, int16_t maxIn, int16_t minOut, int16_t maxOut)
{
   return (value - minIn) * (maxOut - minOut) / (maxIn - minIn) + minOut;
}

int32_t mapValue32(int32_t value, int32_t minIn, int32_t maxIn, int32_t minOut, int32_t maxOut)
{
   return (value - minIn) * (maxOut - minOut) / (maxIn - minIn) + minOut;
}
*/

/*
//NOTE: stolen from K&R p. 64 itoa function
void itoa(int n, char s[])
{
   int i, sign;
   
   if ((sign = n) < 0) // record sign
      n = -n;			// make n positive
   
   i = 0;
   do {	// generate digits in reverse order
      s[i++] = n % 10 + '0'; // get next digit
   } while ((n /= 10) > 0); // delete it
   
   if (sign < 0)
      s[i++] = '-';

   s[i] = '\0'; // add null terminator for string
   reverse(s);
}

//NOTE: stolen from K&R p. 62 reverse function
// reverse: reverse a string s in place
void reverse(char s[])
{
   int c, i, j;
   
   for (i = 0, j = strlen(s)-1; i < j; i++, j--){
      c = s[i];
      s[i] = s[j];
      s[j] = c;
   }
}

void itoa( int val, char *s )
{
   char *p;
   unsigned char d, i;
   unsigned char zero;
   unsigned int test;
   unsigned int uval = val;

   p = s;
   
   if( val < 0 ){
      uval = -val;
      *p++ = '-';
   }

   zero = 1;

   i = 4;
   do {
      i--;
      if (i==0) test = 10;
      else if (i==1) test=100;
      else if (i==2) test=1000;
      else test=10000;

      for (d = '0'; uval >= test; uval -= test )
      {
         d++;
         zero = 0;
      }
     
      if (zero == 0)
         *p++ = d;
   } while (i);

   *p++ = (unsigned char) uval + '0';
}
*/