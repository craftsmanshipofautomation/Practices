#include "encoding.h"
#include <ctype.h>

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

void hexify(char in, char out[2])
{
   int left = (uchar(in) & left_mask) >> 4;
   int right = uchar(in) & right_mask;
   out[0] = Decimal_To_Hex[left];
   out[1] = Decimal_To_Hex[right];
}