#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>

#include "TreeNode.h"
#include "Array.h"
#include "Exception.h"
#include <memory>
#include <cassert>

template <class S, class T>
class AVLTree {
private:

    std::shared_ptr<TreeNode<S,T>> root;

    static void DestroyTree(std::shared_ptr<TreeNode<S,T>> &current);
    static void RollRight(std::shared_ptr<TreeNode<S,T>> &root);
    static void RollLeft(std::shared_ptr<TreeNode<S,T>> &root);

    void BalanceUpwards(std::shared_ptr<TreeNode<S,T>> start);
    void RemoveReplacer(TreeNode<S,T> &target);

    std::shared_ptr<TreeNode<S,T>> GetNode(const S &key);

public:

    AVLTree(): root(nullptr) {}
    AVLTree(const AVLTree& other) = delete;
    AVLTree & operator=(const AVLTree &other) = delete;
    ~AVLTree();

    T& GetItem(const S &key);
    const T& GetItem(const S &key) const;
    void Insert(const S &key, const T &data);
    void Remove(const S &key);

    class iterator;
    iterator begin()
    {
        return iterator(root, root->height);
    }
    iterator end()
    {
        return iterator(nullptr, root->height);
    }
    class const_iterator;
    const_iterator begin() const
    {
        return const_iterator(root, root->height);
    }
    const_iterator end() const
    {
        return const_iterator(nullptr, root->height);
    }
};

template <class S, class T>
class AVLTree<S,T>::iterator {
private:

    friend class AVLTree<S,T>;

    Array stack;
    int top;
    std::shared_ptr<TreeNode<S,T>> current;

    iterator(const std::shared_ptr<TreeNode<S,T>>& current, int height):
        current(current), stack(height + 1), top(0)
    {
        ++(*this);
    }

public:
    iterator() = delete;
    iterator(const iterator &other) = default;
    iterator& operator=(const iterator &other)  = default;
    ~iterator() = default;

    T& operator*()
    {
        assert(current != nullptr);
        return current->data;
    }
    iterator& operator++()
    {
        assert(current != nullptr);
        while(true) {
            if (current == nullptr) {
                return *this;
            }
            if (stack[top].timeViewed == 0) {
                stack[top].timeViewed = 1;
                if (current->right != nullptr) {
                    current = current->right;
                    ++top;
                }
                continue;
            }
            if (stack[top].timeViewed == 1) {
                stack[top].timeViewed = 2;
                return *this;
            }
            if (stack[top].timeViewed == 2) {
                stack[top].timeViewed = 3;
                if (current->left != nullptr) {
                    current = current->left;
                    ++top;
                }
                continue;
            }
            if (stack[top].timeViewed == 3) {
                stack[top].timeViewed = 0;
                --top;
                current = current->top;
                continue;
            }
        }
    }
    iterator operator++(int)
    {
        assert(current != nullptr);
        iterator output = *this;
        ++(*this);
        return output;
    }

    bool operator==(const iterator& other) const
    {
        if ((this->current != other.current) || (this->top != other.top) || (this->stack.GetSize() != other.stack.GetSize())) {
            return false;
        }
        for(int i = 0; i < stack.GetSize(); ++i) {
            if (stack[i].timeViewed != other.stack[i].timeViewed) {
                return false;
            }
        }
        return true;
    }
    bool operator!=(const iterator& other) const
    {
        return !((*this)==other);
    }
};

template <class S, class T>
class AVLTree<S,T>::const_iterator {
private:
private:

    friend class AVLTree<S,T>;

    Array stack;
    int top;
    std::shared_ptr<TreeNode<S,T>> current;

    const_iterator(const std::shared_ptr<TreeNode<S,T>>& current, int height):
    current(current), stack(height + 1), top(0)
    {
        ++(*this);
    }

public:
    const_iterator() = delete;
    const_iterator(const const_iterator &other) = default;
    const_iterator& operator=(const const_iterator &other)  = default;
    ~const_iterator() = default;

    const T& operator*() const
    {
        assert(current != nullptr);
        return current->data;
    }
    const_iterator& operator++()
    {
        assert(current != nullptr);
        while(true) {
            if (current == nullptr) {
                return *this;
            }
            if (stack[top].timeViewed == 0) {
                stack[top].timeViewed = 1;
                if (current->right != nullptr) {
                    current = current->right;
                    ++top;
                }
                continue;
            }
            if (stack[top].timeViewed == 1) {
                stack[top].timeViewed = 2;
                return *this;
            }
            if (stack[top].timeViewed == 2) {
                stack[top].timeViewed = 3;
                if (current->left != nullptr) {
                    current = current->left;
                    ++top;
                }
                continue;
            }
            if (stack[top].timeViewed == 3) {
                stack[top].timeViewed = 0;
                --top;
                current = current->top;
                continue;
            }
        }
    }
    const_iterator operator++(int)
    {
        assert(current != nullptr);
        iterator output = *this;
        ++(*this);
        return output;
    }

    bool operator==(const const_iterator& other) const
    {
        if (this->current != other.current || this->top != other.top || stack.GetSize() != other.stack.GetSize()) {
            return false;
        }
        for(int i = 0; i < stack.GetSize(); ++i) {
            if (stack[i].timeViewed != other.stack[i].timeViewed) {
                return false;
            }
        }
        return true;
    }
    bool operator!=(const const_iterator& other) const
    {
        return !((*this)==other);
    }
};

template <class S, class T>
AVLTree<S,T>::~AVLTree()
{
    DestroyTree(root);
    root = nullptr;
}

template <class S, class T>
void AVLTree<S,T>::DestroyTree(std::shared_ptr<TreeNode<S,T>> &current)
{
    if (current == nullptr) {
        return;
    }
    std::shared_ptr<TreeNode<S,T>> left = current->left;
    if(left != nullptr) {
        left->top = nullptr;
        current->left = nullptr;
    }
    DestroyTree(left);
    std::shared_ptr<TreeNode<S,T>> right = current->right;
    if (right != nullptr) {
        right->top = nullptr;
        current->right = nullptr;
    }
    DestroyTree(right);
}

template <class S, class T>
void AVLTree<S,T>::RollRight(std::shared_ptr<TreeNode<S,T>> &root)
{
    std::shared_ptr<TreeNode<S,T>> left = root->left;
    std::shared_ptr<TreeNode<S,T>> swing = left->right;
    root->left = swing;
    swing->top = root;
    left->right = root;
    left->top = root->top;
    root->top = left;
    if (left->top != nullptr) {
        if (left->top->right == root) {
            left->top->right = left;
        } else {
            assert(left->top->left == root);
            left->top->left = left;
        }
    }
}

template <class S, class T>
void AVLTree<S,T>::RollLeft(std::shared_ptr<TreeNode<S,T>> &root)
{
    std::shared_ptr<TreeNode<S,T>> right = root->right;
    std::shared_ptr<TreeNode<S,T>> swing = right->left;
    root->right = swing;
    swing->top = root;
    right->right = root;
    right->top = root->top;
    root->top = right;
    if (right->top != nullptr) {
        if (right->top->right == root) {
            right->top->right = right;
        } else {
            assert(right->top->left == root);
            right->top->left = right;
        }
    }
}

template <class S, class T>
void AVLTree<S,T>::BalanceUpwards(std::shared_ptr<TreeNode<S,T>> start)
{
    while(true) {
        if (start->balanceFactor() == 2) {
            if (start->left->balanceFactor() == -1) {
                RollLeft(start->left);
            }
            RollRight(start);
        } else if (start->balanceFactor() == -2) {
            if (start->right->balanceFactor() == 1) {
                RollRight(start->right);
            }
            RollLeft(start);
        }
        start->update_height();
        if (start->top == nullptr) {
            break;
        }
        start = start->top;
    }
}

template <class S, class T>
void AVLTree<S,T>::RemoveReplacer(TreeNode<S,T> &target)//DANGEROUS
{
    assert(target.left != nullptr && target.right != nullptr);
    std::shared_ptr<TreeNode<S,T>> temp = target.right;
    bool hasMoved = false;
    while (temp->left != nullptr) {
        hasMoved = true;
        temp = temp->left;
    }
    target.data = temp->data;
    target.key = temp->key;
    std::shared_ptr<TreeNode<S,T>> parent = temp->top;
    if (hasMoved) {
        parent->left = temp->right;
        if (temp->right != nullptr) {
            temp->right->top = parent;
        }
        temp->top = nullptr;
        temp->right = nullptr;
        BalanceUpwards(parent);
    } else {
        parent->right = temp->right;
        if (temp->right != nullptr) {
            temp->right->top = parent;
        }
        temp->top = nullptr;
        temp->right = nullptr;
        BalanceUpwards(parent);
    }
}

template <class S, class T>
std::shared_ptr<TreeNode<S,T>> AVLTree<S,T>::GetNode(const S &key)
{
    std::shared_ptr<TreeNode<S,T>> current = root;
    std::shared_ptr<TreeNode<S,T>> parent = current;
    while(current != nullptr) {
        if (key == current->key) {
            return current;
        }
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return parent;
}

template <class S, class T>
T& AVLTree<S,T>::GetItem(const S &key)
{
    std::shared_ptr<TreeNode<S,T>> ptr = GetNode(key);
    if (ptr->key != key) {
        throw ItemNotFound();
    }
    return ptr->data;
}

template <class S, class T>
const T& AVLTree<S,T>::GetItem(const S &key) const
{
    std::shared_ptr<TreeNode<S,T>> ptr = GetNode(key);
    if (ptr->key != key) {
        throw ItemNotFound();
    }
    return ptr->data;
}

template <class S, class T>
void AVLTree<S,T>::Insert(const S &key,const  T &data)
{
    if (root == nullptr) {
        root = std::shared_ptr<TreeNode<S,T>> (new TreeNode<S,T>(key, data));
        return;
    }
    std::shared_ptr<TreeNode<S,T>> CHECK1 = GetNode(key);
    if (key == CHECK1->key) {
        throw ItemFound();
    }
    std::shared_ptr<TreeNode<S,T>> temp = nullptr;
    if (key < CHECK1->key) {
        assert(CHECK1->left == nullptr);
        CHECK1->left = new TreeNode<S,T> (key, data);
        CHECK1->left->top = CHECK1;
        temp = CHECK1->left;
    } else {
        assert(CHECK1.right == nullptr);
        CHECK1->right = new TreeNode<S,T> (key, data);
        CHECK1->right->top = CHECK1;
        temp = CHECK1->right;
    }
    BalanceUpwards(temp);
}

template <class S, class T>
void AVLTree<S,T>::Remove(const S &key)//DANGEROUS
{
    TreeNode<S,T> toRemove = GetNode(key);
    if(toRemove.key != key) {
        throw ItemNotFound();
    }
    if (toRemove == *root) {
        if (root->left == nullptr && root->right == nullptr) {
            root = nullptr;
            return;
        }
        if (root->left == nullptr)  {
            assert(root->right != nullptr);
            root = root->right;
            root->top->right = nullptr;
            root->top = nullptr;
            return;
        }
        if (root->right == nullptr)  {
            assert(root->left != nullptr);
            root = root->left;
            root->top->left = nullptr;
            root->top = nullptr;
            return;
        }
        RemoveReplacer(toRemove);
    }
    bool isRightChild = key > toRemove.top->key;
    if ( toRemove.left == nullptr &&  toRemove.right == nullptr)
    {
        if (isRightChild) {
            toRemove.top->right = nullptr;
        } else {
            toRemove.top->left = nullptr;
        }
        std::shared_ptr<TreeNode<S,T>> temp = toRemove.top;
        toRemove.top = nullptr;
        BalanceUpwards(*temp);//DANGEROUS
        return;
    }
    if (toRemove.left == nullptr) {
        assert(toRemove.right != nullptr);
        std::shared_ptr<TreeNode<S,T>> temp = toRemove.top;
        if (isRightChild) {
            toRemove.top->connectRight(*toRemove.right);
        } else {
            toRemove.top->connectLeft(*toRemove.right);
        }
        toRemove.top = nullptr;
        toRemove.right = nullptr;
        BalanceUpwards(*temp);//DANGEROUS
        return;
    }
    if (toRemove.right == nullptr) {
        assert(toRemove.left != nullptr);
        std::shared_ptr<TreeNode<S,T>> temp = toRemove.top;
        if (isRightChild) {
            toRemove.top->connectRight(*toRemove.left);
        } else {
            toRemove.top->connectLeft(*toRemove.left);
        }
        toRemove.top = nullptr;
        toRemove.left = nullptr;
        BalanceUpwards(*temp);//DANGEROUS
        return;
    }
    RemoveReplacer(toRemove);
}
#endif //AVLTREE_H
