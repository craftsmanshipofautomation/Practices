#include "libcxx.h"


class Solution {
public:
    static ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* ret = new ListNode(0);
        ListNode* p = ret;
        ListNode** tmp;
        while (l1 && l2)
        {
            if (l1->val < l2->val)
                tmp = &l1;
            else
                tmp = &l2;
            p->next = *tmp;
            p = *tmp;
            *tmp = (*tmp)->next;
        }
        if (!l1)
            p->next = l2;
        if (!l2)
            p->next = l1;
        p = ret->next;
        delete ret;
        return p;
    }
};

int main()
{
    ListNode* a = CreateListNodeFromVector({1, 2, 3, 10, 12, 54});
    ListNode* b = CreateListNodeFromVector({2, 3, 12, 39, 42, 52});
    ListNode* c = Solution::mergeTwoLists(a, b);
    PrintListNode(c);
    CleanListNode(c);

}