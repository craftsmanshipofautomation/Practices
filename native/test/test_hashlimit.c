#include <stdlib.h>
#include <stdio.h>
#include <linux/types.h>

#define HZ 100
#define U32_MAX		((__u32)~0U)

#define XT_HASHLIMIT_BYTE_SHIFT 4

#define _POW2_BELOW2(x) ((x)|((x)>>1))
#define _POW2_BELOW4(x) (_POW2_BELOW2(x)|_POW2_BELOW2((x)>>2))
#define _POW2_BELOW8(x) (_POW2_BELOW4(x)|_POW2_BELOW4((x)>>4))
#define _POW2_BELOW16(x) (_POW2_BELOW8(x)|_POW2_BELOW8((x)>>8))
#define _POW2_BELOW32(x) (_POW2_BELOW16(x)|_POW2_BELOW16((x)>>16))
#define _POW2_BELOW64(x) (_POW2_BELOW32(x)|_POW2_BELOW32((x)>>32))
#define POW2_BELOW32(x) ((_POW2_BELOW32(x)>>1) + 1)

#define MAX_CPJ_BYTES (0xFFFFFFFF / HZ)
#define CREDITS_PER_JIFFY_BYTES POW2_BELOW32(MAX_CPJ_BYTES)

//static __u32 user2credits_byte(__u32 user)
//{
//	__u64 us = user;
//	us *= HZ * CREDITS_PER_JIFFY_BYTES;
//	return (__u32) (us >> 32);
//}

static __u64 user2rate_bytes(__u32 user)
{
	__u64 r;

	r = user ? U32_MAX / user : U32_MAX;
	return (r - 1) << XT_HASHLIMIT_BYTE_SHIFT;
}

int main()
{
    __u64 a = user2rate_bytes(6250);
    printf("%llu\n", a);
}