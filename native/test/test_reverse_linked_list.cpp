struct Vector
{
    
    ~Vector() { delete[] array; }
    ListNode** head, **tail;
    ListNode** array;
    int size;
    Vector(int len) {
        array = new ListNode*[len];
        head = array;
        tail = head;
        size = 0;
    }
    void Push(ListNode* e)
    {
        *tail++ = e;
        ++size; 
    }
    ListNode* back() { return *tail; }
    void Pop()
    {
        if (tail != head)
        {
            --size;
            --tail;
        }
    }
    ListNode* back(return )
    private:
    Vector() {}
};

struct ListNode
{
    ListNode(int v):val(v), next(nullptr) {}
    int val;
    struct ListNode* next;
};

ListNode* arr2LL(int *arr, int size)
{
    if (size < 1) return nullptr;
    ListNode *head = new ListNode(arr[0]), *curr = head;
    for (int i = 0; i < size; ++i)
    {
        ListNode *n = new ListNode(arr[i]);
        curr->next = n;
        curr = n;
    }
    curr->next = nullptr;
    return head;
}

ListNode* reverse(ListNode* ll, int size)
{
    Vector v(size);
    ListNode* curr = ll;
    while (curr)
    {
        v.Push(curr);
        curr = curr->next;
    }
    ListNode* head = new ListNode(0), *curr = head;
    for (int i = 0; i < v.size; ++i)
    {
        ListNode * t = v.back();
        curr->next = t;
        curr = t;
        v.Pop();
    }
    ListNode *ret = head->next;
    delete head;
    return ret;
}

#include <iostream>

int main()
{
    int arr[6] = {1, 2, 3, 4, 5, 6};
    ListNode* testll = arr2LL(arr, 6);
    ListNode* ret = reverse(testll, 6);
    for (int i = 0; i < 6; ++i)
    {
        std::cout << ret->val << std::endl;
        ret = ret->next;
    }

}


thread_info（线程）

-> *task -> task_struct(进程) -- shangxiawen 

ELF ----》内存(stack, heap, page table)




udp,tcp datagram, 
2port len checksum, 

tcp: ack
3-way 
client ->syn(random)  SYN FLOOD
server_> syn+ ack(syn+1)
client ->ack









