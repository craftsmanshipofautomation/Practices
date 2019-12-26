#include "list.h"
#include <assert.h>

// https://kernelnewbies.org/FAQ/LinkedLists

struct mystruct {
    int data;
    struct list_head mylist;
};

int main() 
{
    struct mystruct a = {
        .data = 1,
        .mylist = LIST_HEAD_INIT(a.mylist)
    };

    struct mystruct b = {
        .data = 2,
        .mylist = LIST_HEAD_INIT(b.mylist)
    };
    
    LIST_HEAD(mylinkedlist);
    list_add (&a.mylist, &mylinkedlist);
    list_add (&b.mylist, &mylinkedlist);
    




}