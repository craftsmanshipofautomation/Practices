#ifndef LIB_ENCODING_H
#define LIB_ENCODING_H


#include "libcxx.h"

/**
 * first of all, the system locale thing break an input character
 *  into some sort of numbers
 * for example α, by UTF-8 encoder, is broken in to CE, B1
 * while 读: E8, AF, BB
 */

typedef unsigned char uchar;
// return true if that character need a % prefix
// decimal to hex string, 2 character space width is enough
bool base64_encode(char in, char out[2]);


#endif