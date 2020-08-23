#include "list.h"
#include <assert.h>
#include <stddef.h>
#include "libc.h"

// https://kernelnewbies.org/FAQ/LinkedLists

struct package {
    int data;
    struct list_head list;
};

void pkg_init(struct package *pkg, int data)
{
    pkg->data = data;
    INIT_LIST_HEAD(&(pkg->list));
}

int main() 
{
    struct package a, b;
    pkg_init(&a, 1);
    pkg_init(&b, 2);

    LIST_HEAD(mylinkedlist);

    list_add_tail(&a.list, &mylinkedlist);
    list_add_tail(&b.list, &mylinkedlist);




    struct package *pkg = NULL ; 

    lzlog("", s);
    list_for_each_entry(pkg, &mylinkedlist, list)
    {
        printf("%d\n", pkg->data);
    }

    LIST_HEAD(mylinkedlist2);
    mylinkedlist2 = mylinkedlist;

    lzlog("", s);
    list_for_each_entry(pkg, &mylinkedlist2, list)
    {
        printf("%d\n", pkg->data);
    }


    lzlog("", s);
    list_for_each_entry_reverse(pkg, &mylinkedlist, list)
    {
        printf("%d\n", pkg->data);
    }


}