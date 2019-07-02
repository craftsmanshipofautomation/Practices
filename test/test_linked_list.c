#include "libc.h"


int main()
{
    struct linked_list*  list = linked_list_alloc();
    linked_list_init(&list);
    linked_list_insert(list, 1);    
    linked_list_insert(list, 2);
    linked_list_insert(list, 3);
    linked_list_insert(list, 4);
    linked_list_insert(list, 5);
    linked_list_insert(list, 6);    
    linked_list_print(list);
    linked_list_reverse(list);
    linked_list_print(list);
    
    
    linked_list_reverse(list);
    linked_list_print(list);
    
    linked_list_reverse(list);
    linked_list_print(list);
    
    linked_list_reverse(list);
    linked_list_print(list);
    
    
    
    
    
    linked_list_destroy(&list);
}