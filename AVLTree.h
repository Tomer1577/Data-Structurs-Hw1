#ifndef AVLTREE_H
#define AVLTREE_H

#include "TreeNode.h"
#include "Array.h"
#include <memory>
#include <cassert>

template <class S, class T>
class AVLTree {
private:

    std::shared_ptr<TreeNode<S,T>> root;

    static void DestroyTree(std::shared_ptr<TreeNode<S,T>> &current);
    static void RollRight(TreeNode<S,T> &root);
    static void RollLeft(TreeNode<S,T> &root);

    void BalanceUpwards(TreeNode<S,T> &start);
    void RemoveReplacer(TreeNode<S,T> &target);

    TreeNode<S,T>& GetNode(const S &key);
    const TreeNode<S,T>& GetNode(const S &key) const;

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

    iterator(std::shared_ptr<TreeNode<S,T>> current, int height):
        current(current), stack(height + 1), top(0) {}

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
                if (current->left != nullptr) {
                    current = current->left;
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
                if (current->right != nullptr) {
                    current = current->right;
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

    const_iterator(std::shared_ptr<TreeNode<S,T>> current, int height):
    current(current), stack(height + 1), top(0) {}

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
                if (current->left != nullptr) {
                    current = current->left;
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
                if (current->right != nullptr) {
                    current = current->right;
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
void AVLTree<S,T>::RollRight(TreeNode<S,T> &root)
{
    std::shared_ptr<TreeNode<S,T>> left = root->left;
    std::shared_ptr<TreeNode<S,T>> swing = left->right;
    root->connectLeft(*swing);
    left->connectRight(*root);
    left.top = nullptr;
}

template <class S, class T>
void AVLTree<S,T>::RollLeft(TreeNode<S,T> &root)
{
    TreeNode<S,T> right = root.right;
    TreeNode<S,T> swing = right.left;
    root.connectRight(swing);
    right.connectLeft(root);
    right.top = nullptr;
}

template <class S, class T>
void AVLTree<S,T>::BalanceUpwards(TreeNode<S,T> &start)
{
    TreeNode<S,T> index = start;
    while(true) {
        if (index.balanceFactor() == 2) {
            if (index.left->balanceFactor() == -1) {
                RollLeft(*(index.left));
            }
            RollRight(index);
        } else if (index.balanceFactor() == -2) {
            if (index.right->balanceFactor() == 1) {
                RollRight(*(index.right));
            }
            RollLeft(index);
        }
        index.update_height();
        if (index.top == nullptr) {
            break;
        }
        index = *(index.top);
    }
}

template <class S, class T>
void AVLTree<S,T>::RemoveReplacer(TreeNode<S,T> &target)
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
        BalanceUpwards(*parent);
    } else {
        parent->right = temp->right;
        if (temp->right != nullptr) {
            temp->right->top = parent;
        }
        temp->top = nullptr;
        temp->right = nullptr;
        BalanceUpwards(*parent);
    }
}

template <class S, class T>
TreeNode<S,T>& AVLTree<S,T>::GetNode(const S &key)
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
    return *parent;
}

template <class S, class T>
const TreeNode<S,T>& AVLTree<S,T>::GetNode(const S &key) const
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
    return *parent;
}

template <class S, class T>
T& AVLTree<S,T>::GetItem(const S &key)
{
    return GetNode(key).data;
}

template <class S, class T>
const T& AVLTree<S,T>::GetItem(const S &key) const
{
    return GetNode(key).data;
}

template <class S, class T>
void AVLTree<S,T>::Insert(const S &key,const  T &data)
{
    if (root == nullptr) {
        root = std::shared_ptr<TreeNode<S,T>> (TreeNode<S,T>(key, data));
    }
    TreeNode<S,T> parent = GetNode(key);
    if (key == parent.key) {//item already exists
        TODO;//throw
        return;
    }
    TreeNode<S,T> newNode(key, data);
    if (key < parent.key) {
        assert(parent.left == nullptr);
        parent.connectLeft(newNode);
    } else {
        assert(parent.right == nullptr);
        parent.connectRight(newNode);
    }
    balanceUpwards(newNode);
}

template <class S, class T>
void AVLTree<S,T>::Remove(const S &key) //using the lecture's algorithm
{
    TreeNode<S,T> toRemove = GetNode(key);
    if(toRemove.key != key) {//item not found
        TODO;//throw
        return;
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
        BalanceUpwards(*temp);
        return;
    }
    if (toRemove.left == nullptr) {
        assert(toRemove.right != nullptr);
        std::shared_ptr<TreeNode<S,T>> temp = toRemove.top;
        if (isRightChild) {
            toRemove.top->connectRight(toRemove.right);
        } else {
            toRemove.top->connectLeft(toRemove.right);
        }
        toRemove.top = nullptr;
        toRemove.right = nullptr;
        BalanceUpwards(*temp);//note that right's subtree is unaffected by the function, so it can start with right
        return;
    }
    if (toRemove.right == nullptr) {
        assert(toRemove.left != nullptr);
        std::shared_ptr<TreeNode<S,T>> temp = toRemove.top;
        if (isRightChild) {
            toRemove.top->connectRight(toRemove.left);
        } else {
            toRemove.top->connectLeft(toRemove.left);
        }
        toRemove.top = nullptr;
        toRemove.left = nullptr;
        BalanceUpwards(*temp);//refer to the comment on (left == null) block
        return;
    }
    RemoveReplacer(toRemove);
}
#endif //AVLTREE_H
