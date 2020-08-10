#include <climits>
#include <cstring>
#include <functional>
#include <iostream>
#include <stack>

struct Node
{
    Node(int v) : value(v), left(nullptr), right(nullptr), parent(nullptr) {}
    void eat(int v)
    {
        Node *n = new Node(v);
        Node *r = this;
        Node **pp;
        while (1)
        {
            pp = v > value ? &(r->right) : &(r->left);
            if (*pp)
                r = *pp;
            else
            {
                *pp = n;
                n->parent = r;
                break;
            }
        }
    }
    int value;
    Node *left;
    Node *right;
    Node *parent;
    static void kill(Node *n) { delete n; }
    static void show(Node *n) { std::cout << n->value << " "; }
    static void show_parent(Node *n)
    {
        std::cout << n->value << "->" << ((n->parent) ? n->parent->value : -1)
                  << std::endl;
    }
};

class Tree
{
  public:
    Tree(int *arr, int size) : root_(nullptr)
    {
        if (size)
            root_ = new Node(arr[0]);
        for (int i = 1; i < size; ++i)
        {
            root_->eat(arr[i]);
        }
    }
    ~Tree() { traverse(Node::kill); }
    void traverse(std::function<void(Node *)> f)
    {
        if (!root_)
            return;
        std::stack<Node *> stack_;
        stack_.push(root_);
        Node *curr;
        while (stack_.size())
        {
            curr = stack_.top();
            stack_.pop();
            if (curr->left)
                stack_.push(curr->left);
            if (curr->right)
                stack_.push(curr->right);
            f(curr);
        }
    }
    void show()
    {
        traverse(Node::show);
        std::cout << std::endl;
    }
    void show2() { traverse(Node::show_parent); }

  private:
    Node *root_;
};

int main()
{
    int arr[20] = {1, 0, 12, 14, 5,  16, 11, 19, 6, 4,
                   2, 3, 13, 17, 18, 10, 15, 8,  9, 7};
    Tree tree(arr, 20);
    tree.show();
    tree.show2();
}