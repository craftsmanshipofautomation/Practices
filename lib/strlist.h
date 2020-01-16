#ifndef STRLIST_H
#define STRLIST_H

#include "list.h"
#include <string.h>
#include <stddef.h>


#define sl_list_for_each_entry(pos, head) list_for_each_entry(pos, head, link)


struct strnode {
    char *str;
    struct list_head link;
};

static inline void sl_append(struct list_head* head, char * input)
{
    struct strnode * a = (struct strnode *)malloc(sizeof(struct strnode));
    a->str = strdup(input);
    INIT_LIST_HEAD(&a->link);
    list_add_tail(&a->link, head);
}

static inline void sl_free(struct list_head* head)
{
    struct list_head *curr = head->next, *next;
    struct strnode* node;
    while (curr != head)
    {
        next = curr->next;
        node = list_entry(curr, struct strnode, link);
        list_del(curr);
        free(node->str);
        free(node);
        curr = next;
    }
    // don't delete the head
}

static inline void sl_show(struct list_head* head)
{
    struct strnode *pkg = NULL ;
    sl_list_for_each_entry(pkg, head)
    {
        printf("%s ", pkg->str);
    }
    printf("\n");
}





#endif
