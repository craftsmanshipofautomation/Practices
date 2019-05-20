/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#include "libc.h"

struct ListNode {
    int val;
    struct ListNode *next;
};
 
int add(int lhs, int rhs, int extra, int* sum)
{
    int overflow;
    int raw_sum = lhs + rhs + extra;
    if (raw_sum >= 10)
    {
        overflow = 1;
        *sum = raw_sum - 10;
    }
    else
    {
        overflow = 0;
        *sum = raw_sum;
    }
    return overflow;
}

typedef struct ListNode *LN;

LN MakeList(int len, int* arr)
{
    LN head, new;
    head = new = malloc(sizeof(struct ListNode));
    int i;
    for (i = 0; i < len-1; ++i)
    {
        new->val = arr[i];
        new->next = malloc(sizeof(struct ListNode));
        new = new->next;
    }
    new->val = arr[len-1];
    new->next = NULL;
    return head;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    int sum[100];
    int prog = 0;
    int overflow = 0;
    int maxlen;
    LN t1 = l1;
    LN t2 = l2;
    LN longer;
    LN new;
    while (t1 && t2)
    {
        overflow = add(t1->val, t2->val, overflow, sum + prog);
        ++prog;
        t1 = t1->next;
        t2 = t2->next;
    }
    maxlen = prog;
    longer = t1 ? t1 : t2;
    while (longer)
    {
        overflow = add(0, longer->val, overflow, sum + prog);
        ++prog;
        longer = longer->next;
    }
    maxlen = prog;
    if (overflow)
    {
        ++maxlen;
        sum[prog] = 1;
    }
    new = MakeList(maxlen, sum);
    return new;
    
}

int main()
{
   
}