#include "libc.h"
#include "strlist.h"



int main()
{
    LIST_HEAD(fuck);
    sl_append(&fuck, "123");
    sl_append(&fuck, "abc");
    sl_append(&fuck, "456");
    sl_append(&fuck, "efg");

    sl_show(&fuck);

    sl_free(&fuck);

}


