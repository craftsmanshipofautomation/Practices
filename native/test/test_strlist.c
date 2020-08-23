#include "libc.h"
#include "strlist.h"

/*
// example 1
    LIST_HEAD(fuck);
    sl_append(&fuck, "123");
    sl_append(&fuck, "abc");
    sl_append(&fuck, "456");
    sl_append(&fuck, "efg");
    sl_show(&fuck);

    LIST_HEAD(son_of_a_bitch);
    sl_append(&son_of_a_bitch, "jkl");
    sl_show(&son_of_a_bitch);

    sl_concat(&fuck, &son_of_a_bitch);
    sl_show(&fuck);

    sl_free(&fuck);
*/



int main()
{
    struct list_head *fuck = sl_malloc();
    sl_append(fuck, "1");
    sl_append(fuck, "2");
    sl_append(fuck, "3");

    sl_show(fuck);
    sl_free(fuck);


}


