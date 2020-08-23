#include "libc.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode {
    int val;
    struct ListNode *next;
};

typedef struct ListNode * LN;
bool hasCycle(struct ListNode *head) {
    if (!head)
        return false;
    LN slow = head;
    LN fast = slow->next; 
    if (!fast)
        return false;
    while (fast)
    {
        fast = fast->next;
        if (!fast)
        {
            return false;
        }
        fast = fast->next;
        slow = slow->next;
        if (slow == fast)
            return true;
    }
    
    return false;
    
    
    
}

int main()
{
}
