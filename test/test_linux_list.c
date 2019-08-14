#include "list.h"
#include <assert.h>

// a project from my job should use some reasonable data structure, but it didn't;
// hereby I test linux/list.h before I fully utilize it

// just in case someone doesnot wish to use typedef
struct class
{
    int id;
    // references to P
    struct list_head refs2grp;
};

struct clsref
{
    struct class * cls;
    struct list_head neigh;
};

struct group
{
    int id;
    // references to C
    struct list_head refs2class;
};

struct grpref
{
    struct group * grp;
    struct list_head neigh;
};


// 2 classes, 1 group, the group holds references to both classes
// 1. delete classes one by one,
//  when all classed is deleted, group should be also be destroyed
// 2. delete group, all classes will be deleted

int main() 
{
    struct class c1, c2;
    struct group g1;
    INIT_LIST_HEAD(&(c1.refs2grp));
    INIT_LIST_HEAD(&(c2.refs2grp));
    {
        struct grpref *ptr= (struct grpref *)malloc(sizeof (struct grpref));
        ptr->grp = &g1;
        list_add_tail(&(ptr->neigh), &(c1.refs2grp));
        list_add_tail(&(ptr->neigh), &(c2.refs2grp));
    }
    {
        struct clsref *ptr = (struct classref*)malloc(sizeof (struct clsref));
        ptr->cls = &c1;
        list_add_tail(&(ptr->neigh), &(g1.refs2class));
    }
    {
        struct clsref *ptr = (struct classref*)malloc(sizeof (struct clsref));
        ptr->cls = &c2;
        list_add_tail(&(ptr->neigh), &(g1.refs2class));
    }


}