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

    void BalanceUpwards(TreeNode<S,T> &leaf);

    TreeNode<S,T> GetNode(const S &key);

public:

    AVLTree(): root(nullptr) {}
    AVLTree(const AVLTree& other) = delete;
    AVLTree & operator=(const AVLTree &other) = delete;
    ~AVLTree();

    void Insert(const S &key, const T &data);
    void Remove(const S &key);
    T& GetItem(const S &key);
};

template <class S, class T>
AVLTree<S,T>::~AVLTree()
{
    DestroyTree(root);
    root = nullptr;
}

template <class S, class T>
void AVLTree<S,T>::Insert(const S &key,const  T &data)
{
    TreeNode<S,T> newNode(key, data);
    TreeNode<S,T> parent = GetNode(key);
    if (key == parent.key) {
        parent.data = data;
        return;
    }
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
T& AVLTree<S,T>::GetItem(const S &key)
{
    return GetNode(key).data;
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
void AVLTree<S,T>::BalanceUpwards(TreeNode<S,T> &leaf)
{
    TreeNode<S,T> index = leaf;
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
TreeNode<S,T> AVLTree<S,T>::GetNode(const S &key)
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

#endif //AVLTREE_H
