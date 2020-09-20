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

typedef struct ListNode* LN;
bool isPalindrome(struct ListNode* head) {
    if (!head || !head->next)
    {
        return true;
    }
    LN slow, fast, temp, prev;
    slow = fast = head;
    prev = NULL;
    while(fast)
    {
        fast = fast->next ? fast->next->next : fast->next;
        slow = slow->next;
    }
    while (slow)
    {
        temp = slow->next;
        slow->next = prev;
        prev = slow;
        slow = temp;
    }
    temp = head;
    while (prev)
    {
        if (temp->val != prev->val)
        {
            return false;
        }
        temp = temp->next;
        prev = prev->next;
    }
    return true;
}

int main()
{
}
