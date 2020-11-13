#include "libc.h"
#define HZ 100

#define MAX_CPJ_v1 (0xFFFFFFFF / (HZ*60*60*24))
#define MAX_CPJ (0xFFFFFFFFFFFFFFFFULL / (HZ*60*60*24))

#define _POW2_BELOW2(x) ((x)|((x)>>1))
#define _POW2_BELOW4(x) (_POW2_BELOW2(x)|_POW2_BELOW2((x)>>2))
#define _POW2_BELOW8(x) (_POW2_BELOW4(x)|_POW2_BELOW4((x)>>4))
#define _POW2_BELOW16(x) (_POW2_BELOW8(x)|_POW2_BELOW8((x)>>8))
#define _POW2_BELOW32(x) (_POW2_BELOW16(x)|_POW2_BELOW16((x)>>16))
#define _POW2_BELOW64(x) (_POW2_BELOW32(x)|_POW2_BELOW32((x)>>32))
#define POW2_BELOW32(x) ((_POW2_BELOW32(x)>>1) + 1)
#define POW2_BELOW64(x) ((_POW2_BELOW64(x)>>1) + 1)

#define CREDITS_PER_JIFFY POW2_BELOW64(MAX_CPJ)
#define CREDITS_PER_JIFFY_v1 POW2_BELOW32(MAX_CPJ_v1)

/* in byte mode, the lowest possible rate is one packet/second.
 * credit_cap is used as a counter that tells us how many times we can
 * refill the "credits available" counter when it becomes empty.
 */
#define MAX_CPJ_BYTES (0xFFFFFFFF / HZ)
#define CREDITS_PER_JIFFY_BYTES POW2_BELOW32(MAX_CPJ_BYTES)


int main()
{
    lzlog(CREDITS_PER_JIFFY_BYTES, llu);
    lzlog(CREDITS_PER_JIFFY, llu);
    lzlog(MAX_CPJ, llu);
    lzlog(CREDITS_PER_JIFFY_v1, llu);
}