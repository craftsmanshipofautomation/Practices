#include "encoding.h"

char Decimal_To_Hex[16] = {
   '0',
   '1',
   '2',
   '3',
   '4',
   '5',
   '6',
   '7',
   '8',
   '9',
   'A',
   'B',
   'C',
   'D',
   'E',
   'F',
};

uchar left_mask = 240;
uchar right_mask = 15;

bool base64_encode(char in, char out[2])
{
   // base 64
   if ((in >= 65 && in <= 90) || (in >= 97 && in <= 122) 
      || isdigit(in) || in == '+' || in == '/')
      return false;
   int left = (uchar(in) & left_mask) >> 4;
   int right = uchar(in) & right_mask;
   out[0] = Decimal_To_Hex[left];
   out[1] = Decimal_To_Hex[right];   
   return true;
}