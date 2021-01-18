#include "libcxx.h"

class Solution {
public:
    ListNode* subMerge(vector<ListNode*>& lists, int begin, int end)
    {
        if (begin == end)
        {
            return lists[begin];
        }
        int mid = begin + (end - begin) / 2;
        ListNode* left = subMerge(lists, begin, mid);
        ListNode* right = subMerge(lists, mid+1, end);
        // merge 2 shit
        ListNode* head = new ListNode(), *curr = head;
        while (right)
        {
            while (left && left->val <= right->val)
            {
                curr->next = left;
                left = left->next;
                curr = curr->next;
            }
            swap(left, right);
        }
        curr->next = left;
        curr = head->next;
        delete head;
        return curr;
        
    }
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return NULL;
        return subMerge(lists, 0, lists.size() - 1);

        
    }
};

int main()
{
    ListNode * a = CreateListNodeFromVector({1, 4, 5});
    ListNode * b = CreateListNodeFromVector({1, 3, 4});
    ListNode * c = CreateListNodeFromVector({2, 6});
    vector<ListNode*> v = {a, b, c};
    Solution s;
    ListNode* r = s.mergeKLists(v);
    PrintListNode(r);
}
