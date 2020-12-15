#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>

#include "TreeNode.h"
#include "Exception.h"
#include "List.h"
#include <memory>
#include <cassert>

template <class S, class T>
class AVLTree {
private:

    std::shared_ptr<TreeNode<S,T>> root;
    std::shared_ptr<TreeNode<S,T>> first;

    static void DestroyTree(std::shared_ptr<TreeNode<S,T>> &current);
    void RollRight(std::shared_ptr<TreeNode<S,T>> root);
    void RollLeft(std::shared_ptr<TreeNode<S,T>> root);

    void BalanceUpwards(std::shared_ptr<TreeNode<S,T>> start);
    void RemoveReplacer(std::shared_ptr<TreeNode<S,T>> &target);

    std::shared_ptr<TreeNode<S,T>> GetNode(const S &key);

public:

    AVLTree(): root(nullptr), first(nullptr) {}
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
        return iterator(first);
    }
    iterator end()
    {
        return iterator(nullptr);
    }
    class const_iterator;
    const_iterator begin() const
    {
        return const_iterator(first);
    }
    const_iterator end() const
    {
        return const_iterator(nullptr);
    }
};

template <class S, class T>
class AVLTree<S,T>::iterator {
private:

    friend class AVLTree<S,T>;

    std::shared_ptr<TreeNode<S,T>> current;
    List<int> stack;

    explicit iterator(const std::shared_ptr<TreeNode<S,T>>& current): current(current), stack()
    {
        stack.PushFront(2);
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
            if (stack.Front() == 0) {
                stack.Front() = 1;
                if (current->left != nullptr) {
                    current = current->left;
                    stack.PushFront(0);
                }
                continue;
            }
            if (stack.Front() == 1) {
                stack.Front() = 2;
                return *this;
            }
            if (stack.Front() == 2) {
                stack.Front() = 3;
                if (current->right != nullptr) {
                    current = current->right;
                    stack.PushFront(0);
                }
                continue;
            }
            if (stack.Front() == 3) {
                stack.PopFront();
                if (stack.IsEmpty()) {
                    stack.PushFront(1);
                }
                current = current->top;
                continue;
            }
        }
    }
    iterator operator++(int)
    {
        assert(current != nullptr);
        iterator output(*this);
        ++(*this);
        return output;
    }

    bool operator==(const iterator& other) const
    {
        return current == other.current;
    }
    bool operator!=(const iterator& other) const
    {
        return !((*this)==other);
    }
};

template <class S, class T>
class AVLTree<S,T>::const_iterator {
private:

    friend class AVLTree<S,T>;

    std::shared_ptr<TreeNode<S,T>> current;
    List<int> stack;

    explicit const_iterator(const std::shared_ptr<TreeNode<S,T>>& current): current(current), stack()
    {
        stack.PushFront(2);
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
            if (stack.Front() == 0) {
                stack.Front() = 1;
                if (current->right != nullptr) {
                    current = current->right;
                    stack.PushFront(0);
                }
                continue;
            }
            if (stack.Front() == 1) {
                stack.Front() = 2;
                return *this;
            }
            if (stack.Front() == 2) {
                stack.Front() = 3;
                if (current->left != nullptr) {
                    current = current->left;
                    stack.PushFront(0);
                }
                continue;
            }
            if (stack.Front() == 3) {
                stack.PopFront();
                if (stack.IsEmpty()) {
                    stack.PushFront(1);
                }
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
        return current == other.current;
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
    first = nullptr;
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
void AVLTree<S,T>::RollRight(std::shared_ptr<TreeNode<S,T>> root)
{
    assert(root->balanceFactor() == 2 || root->balanceFactor() == 1);
    std::shared_ptr<TreeNode<S,T>> left = root->left;
    assert(left != nullptr);
    std::shared_ptr<TreeNode<S,T>> swing = left->right;
    root->left = swing;
    if (swing != nullptr) {
        swing->top = root;
    }
    left->right = root;
    left->top = root->top;
    root->top = left;
    if (this->root == root) {
        this->root = left;
    }
    if (left->top != nullptr) {
        if (left->top->right == root) {
            left->top->right = left;
        } else {
            assert(left->top->left == root);
            left->top->left = left;
        }
    }
    root->update_height();
    left->update_height();
}

template <class S, class T>
void AVLTree<S,T>::RollLeft(std::shared_ptr<TreeNode<S,T>> root)
{
    assert(root->balanceFactor() == -2 || root->balanceFactor() == -1);
    std::shared_ptr<TreeNode<S,T>> right = root->right;
    assert(right != nullptr);
    std::shared_ptr<TreeNode<S,T>> swing = right->left;
    root->right = swing;
    if (swing != nullptr) {
        swing->top = root;
    }
    right->left = root;
    right->top = root->top;
    root->top = right;
    if (this->root == root) {
        this->root = right;
    }
    if (right->top != nullptr) {
        if (right->top->right == root) {
            right->top->right = right;
        } else {
            assert(right->top->left == root);
            right->top->left = right;
        }
    }
    root->update_height();
    right->update_height();
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
            start = start->top;
        } else if (start->balanceFactor() == -2) {
            if (start->right->balanceFactor() == 1) {
                RollRight(start->right);
            }
            RollLeft(start);
            start = start->top;
        }
        start->update_height();
        if (start->top == nullptr) {
            break;
        }
        start = start->top;
    }
}

template <class S, class T>
void AVLTree<S,T>::RemoveReplacer(std::shared_ptr<TreeNode<S,T>> &target)
{
    assert(target->left != nullptr && target->right != nullptr);
    std::shared_ptr<TreeNode<S,T>> temp = target->right;
    bool hasMoved = false;
    while (temp->left != nullptr) {
        hasMoved = true;
        temp = temp->left;
    }
    target->data = temp->data;
    target->key = temp->key;
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
        first = root;
        return;
    }
    std::shared_ptr<TreeNode<S,T>> parent = GetNode(key);
    if (key == parent->key) {
        throw ItemFound();
    }
    std::shared_ptr<TreeNode<S,T>> temp = nullptr;
    if (key < parent->key) {
        assert(parent->left == nullptr);
        parent->left = std::shared_ptr<TreeNode<S,T>>(new TreeNode<S,T> (key, data));
        parent->left->top = parent;
        temp = parent->left;
        if (parent == first) {
            first = parent->left;
        }
    } else {
        assert(parent->right == nullptr);
        parent->right = std::shared_ptr<TreeNode<S,T>>(new TreeNode<S,T>(key, data));
        parent->right->top = parent;
        temp = parent->right;
    }
    BalanceUpwards(temp);
}

template <class S, class T>
void AVLTree<S,T>::Remove(const S &key)
{
    std::shared_ptr<TreeNode<S,T>> toRemove = GetNode(key);
    if(toRemove->key != key) {
        throw ItemNotFound();
    }
    if (toRemove == root) {
        if (root->left == nullptr && root->right == nullptr) {
            root = nullptr;
            first = nullptr;
            return;
        }
        if (root->left == nullptr)  {
            assert(root->right != nullptr && root == first);
            first = root ->right;
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
        return;
    }
    bool isRightChild = key > toRemove->top->key;
    std::shared_ptr<TreeNode<S,T>> temp = toRemove->top;
    if (toRemove->left == nullptr &&  toRemove->right == nullptr)
    {
        if (toRemove == first) {
            first = toRemove->top;
        }
        if (isRightChild) {
            toRemove->top->right = nullptr;
        } else {
            toRemove->top->left = nullptr;
        }
        toRemove->top = nullptr;
        BalanceUpwards(temp);
        return;
    }
    if (toRemove->left == nullptr) {
        assert(toRemove->right != nullptr);
        if (isRightChild) {
            toRemove->top->right = toRemove->right;
        } else {
            if (toRemove == first) {
                first = toRemove->right;
            }
            toRemove->top->left = toRemove->right;
        }
        toRemove->right->top = toRemove->top;
        toRemove->top = nullptr;
        toRemove->right = nullptr;
        BalanceUpwards(temp);
        return;
    }
    if (toRemove->right == nullptr) {
        assert(toRemove->left != nullptr);
        if (isRightChild) {
            toRemove->top->right = toRemove->left;
        } else {
            toRemove->top->left = toRemove->left;
        }
        toRemove->left->top = toRemove->top;
        toRemove->top = nullptr;
        toRemove->left = nullptr;
        BalanceUpwards(temp);
        return;
    }
    RemoveReplacer(toRemove);
}
#endif //AVLTREE_H
