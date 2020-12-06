#ifndef AVLTREE_H
#define AVLTREE_H

#include "TreeNode.h"
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

    TreeNode<S,T>& GetNode(const S &key);

public:

    AVLTree(): root(nullptr) {}
    AVLTree(const AVLTree& other) = delete;
    AVLTree & operator=(const AVLTree &other) = delete;
    ~AVLTree();

    T& GetItem(const S &key);
    void Insert(const S &key, const T &data);
    void Remove(const S &key);
    
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
T& AVLTree<S,T>::GetItem(const S &key)
{
    return GetNode(key).data;
}

template <class S, class T>
void AVLTree<S,T>::Insert(const S &key,const  T &data)
{
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
    TODO//what if root is removed?
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
    assert(toRemove.left != nullptr && toRemove.right != nullptr);
    std::shared_ptr<TreeNode<S,T>> temp = toRemove.right;
    bool hasMoved = false;
    while (temp->left != nullptr) {
        hasMoved = true;
        temp = temp->left;
    }
    toRemove.data = temp->data;
    toRemove.key = temp->key;
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
#endif //AVLTREE_H
