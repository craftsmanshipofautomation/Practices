#include "libcxx.h"

ListNode* CreateListNodeFromVector(vector<int> nums)
{
    ListNode* head = new ListNode(0), *p = head;
    for (int& i: nums)
    {
        p->next = new ListNode(i);
        p = p->next;
    }
    p->next = nullptr;
    p = head->next;
    delete head;
    return p;
}

void PrintListNode(ListNode* l1)
{
    while (l1)
    {
        lzlog(l1->val, d);
        l1 = l1->next;
    }
}

void CleanListNode(ListNode* l1)
{
    while (l1)
    {
        ListNode* tmp = l1->next;
        delete l1;
        l1 = tmp;
    }
}