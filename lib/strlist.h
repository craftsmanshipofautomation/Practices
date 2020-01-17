#ifndef STRLIST_H
#define STRLIST_H

#include "list.h"
#include <stddef.h>
#include <string.h>


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

static inline int sl_length(struct list_head* head)
{
    int cnt = 0;
    struct strnode *pkg = NULL ;
    list_for_each_entry(pkg, head, link)
    {
        ++ cnt;
    }
    return cnt;
}

/* already defined in list.h
static inline int sl_is_empty(struct list_head* head)
{
    if (head->next == head)
    {
        return true;
    }
    return false;
}

// see list_splice
static inline struct list_head* sl_concat(struct list_head* list1, struct list_head* list2)
{
    // in case list1 is empty
    if (sl_is_empty(list1))
    {
        return list2;
    }
    else if (sl_is_empty(list2))
    {
        return list1;
    }
    // take list2's head off
    struct list_head* lastofl1 = list1->prev;
    struct list_head* firstofl2 = list2->next;
    struct list_head* lastofl2 = list2->prev;
    
    // 1
    lastofl2->next = list1;
    list1->prev = lastofl2;
    // 2
    lastofl1->next = firstofl2;
    firstofl2->prev = lastofl1;

    return list1;
}
*/

// list_splice is against human intuition
static inline void sl_concat(struct list_head* list1, struct list_head* list2)
{
    list_splice(list2, list1->prev);
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
    list_for_each_entry(pkg, head, link)
    {
        printf("%s ", pkg->str);
    }
    printf("\n");
}





#endif
