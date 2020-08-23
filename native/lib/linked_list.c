#include "libc.h"
#include "linked_list.h"


struct linked_list*  linked_list_alloc()
{
    struct linked_list* new = malloc(sizeof (struct linked_list));
    return new;    
}

void linked_list_init(struct linked_list** list)
{
    memset(*list, 0, sizeof(struct linked_list));
}

void linked_list_destroy(struct linked_list** list)
{
    struct list_node * curr = (*list)->nodes;
    struct list_node * temp;    
    while (curr != NULL)
    {
        temp = curr->next;
        free(curr);
        curr = temp;
    }
    free(*list);
    *list = NULL;
}

void linked_list_reverse(struct linked_list* list)
{
    struct list_node * curr = list->nodes;
    struct list_node * prev = NULL, *temp;
    while (curr)
    {
        temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }
    list->nodes = prev;
    list->end = list->begin;
}

struct list_node* make_node(int value)
{
    struct list_node* r = malloc(sizeof (struct linked_list));
    r->value = value;
    r->next = NULL;
    
}

void linked_list_insert(struct linked_list* list, int value)
{
    struct list_node * node = make_node(value);
    if (list->end)
        list->end->next = node;
    else
    {
        list->nodes = node;
        list->begin = node;
    }
    list->end = node;
    list->size ++;
}

void linked_list_print(struct linked_list* list)
{
    struct list_node * curr = list->nodes;
    for(; curr != NULL; curr = curr->next)
    {
        printf("%d ", curr->value);
    }
    printf("\n");
}