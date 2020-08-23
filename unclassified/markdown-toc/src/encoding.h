/**
 * first of all, the system locale thing break an input character
 *  into some sort of numbers
 * for example α, by UTF-8 encoder, is broken in to CE, B1
 * while 读: E8, AF, BB
 */

typedef unsigned char uchar;

// decimal to hex string, 2 character space width is enough
void hexify(char in, char out[2]);
