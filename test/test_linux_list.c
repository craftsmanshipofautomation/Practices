#include "list.h"
#include <assert.h>
#include <stddef.h>

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
    


    struct list_head *position = NULL ; 
    struct mystruct  *datastructureptr  = NULL ; 
    list_for_each ( position , & mylinkedlist ) 
    { 
         datastructureptr = list_entry(position, struct mystruct , mylist); 
         printf("data  =  %d\n" , datastructureptr->data ); 
    }

}