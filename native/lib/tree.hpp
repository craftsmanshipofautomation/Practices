#ifndef PRACTICE_LIB_TREE_HPP
#define PRACTICE_LIB_TREE_HPP

#include <ios>
#include <iostream>
#include <memory>
#include <sstream>

template <typename T> struct BinaryTreeNode
{
    BinaryTreeNode(T e, BinaryTreeNode *l, BinaryTreeNode *r) noexcept
        : value{e}, left_child{l}, right_child{r}
    {
    }
    T value;
    BinaryTreeNode *left_child;
    BinaryTreeNode *right_child;
};

template <typename T, class TreeNode, typename Alloc = std::allocator<T>>
class Tree
{
  public:
    typedef TreeNode Node;
    typedef typename Alloc::template rebind<Node>::other Allocator;

    Tree() noexcept : root_(nullptr) {}
    ~Tree() noexcept { clear(); }

    void insert(Node *&p, T element)
    {
        if (!p)
            {
                Node *new_node = allocator_.allocate(1);
                allocator_.construct(new_node, element, nullptr, nullptr);
                p = new_node;
                return;
            }
        if (element > p->value)
            insert(p->right_child, element);
        else
            insert(p->left_child, element);
    }

    void insert(T element) { insert(root_, element); }

    void clear(Node *node)
    {
        if (!node)
            return;
        if (node->left_child)
            clear(node->left_child);
        if (node->right_child)
            clear(node->right_child);
        allocator_.destroy(node);
        allocator_.deallocate(node, 1);
        node = nullptr;
    }
    void clear()
    {
        clear(root_);
        root_ = nullptr;
    }

    // |   ????   | --[X]--|  NODE  |
    // |<-offset->|<--8--->|<---3-->|
   
    void sub_string(Node *node, std::ostringstream &os, int offset,
                    bool is_left)
    {
        if (!node)
            return;
        if (is_left)
            os << std::setw(offset) << "";        
        if (is_left)
            os << " --[l]--"; // 8
        else
            os << " --[r]--";
        os << std::setw(3) << node->value;
        offset += (8 + 3);
        sub_string(node->right_child, os, offset, false);
        if (node->left_child)
            {
                os << std::endl;
                sub_string(node->left_child, os, offset, true);
            }
    }

    std::string to_string()
    {
        std::ostringstream os;
        os.flags(std::ios::right);
        os << std::setw(3) << root_->value;
        sub_string(root_->right_child, os, 3, false);
        os << std::endl;        
        sub_string(root_->left_child, os, 3, true);
        os << std::endl;
        return os.str();
    }

    T root() { return root_->value; }

  private:
    Allocator allocator_;
    Node *root_;
};

#endif