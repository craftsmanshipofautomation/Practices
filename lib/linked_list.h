#ifndef LIB_LINKED_LIST
#define LIB_LINKED_LIST

typedef struct list_node 
{
    int value;
    struct list_node *next;
} list_node;

struct linked_list
{
    int size;    
    list_node* begin;
    list_node* end;
    list_node* nodes;
};

struct linked_list*  linked_list_alloc();
void linked_list_init(struct linked_list** list);
void linked_list_destroy(struct linked_list** list);
void linked_list_reverse(struct linked_list* list);

struct list_node* make_node(int value);
void linked_list_insert(struct linked_list* list, int value);
void linked_list_print(struct linked_list* list);



#endif