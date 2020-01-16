#ifndef STRLIST_H
#define STRLIST_H

#include "list.h"
#include <string.h>

struct strnode {
    char *str;
    struct list_head* link;
};

static inline void sl_append(struct list_head* head, char * input)
{
    struct strnode * a = (struct strnode *)malloc(sizeof(struct strnode));
    a->str = strdup(input);
    INIT_LIST_HEAD(a->link);
    list_add_tail(a->link, head);
}

static inline void sl_free(struct list_head* head)
{
    struct list_head *curr = head, *next;
    struct strnode* node;
    next = curr->next;
    while (next != head)
    {
        curr = next;
        next = curr->next;
        node = list_entry(curr, struct strnode, link);
        list_del(curr);
        free(node->str);
    }
    // don't delete the head
}





#endif
