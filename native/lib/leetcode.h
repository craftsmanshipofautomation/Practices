struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
    ListNode(): val(0), next(NULL) {}
};

ListNode* CreateListNodeFromVector(vector<int> nums);
void PrintListNode(ListNode*);
void CleanListNode(ListNode*);