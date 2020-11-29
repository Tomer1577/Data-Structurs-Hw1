#ifndef AVLTREE_H
#define AVLTREE_H

#include "TreeNode.h"
#include <memory>
#include <cassert>

template <class T>
class AVLTree {
private:

    std::shared_ptr<TreeNode<T>> root;

    static void DestroyTree(std::shared_ptr<TreeNode<T>> &current);
    static void RollRight(TreeNode<T> &root);
    static void RollLeft(TreeNode<T> &root);

    void BalanceUpwards(TreeNode<T> &root);

    TreeNode<T> GetNode(int key);

public:

    AVLTree(): root(nullptr) {}
    AVLTree(const AVLTree& other) = delete;
    AVLTree & operator=(const AVLTree &other) = delete;
    ~AVLTree();

    void Insert(int key, T& data);
    void Remove(int key);
    T& GetItem(int key);
};

template <class T>
AVLTree<T>::~AVLTree()
{
    DestroyTree(root);
    root = nullptr;
}

template <class T>
void AVLTree<T>::Insert(int key, T& data)
{
    TreeNode<T> newNode(key,data);
    TreeNode<T> parent = GetNode(key);
    if (key == parent.key) {
        parent.data = data;
        return;
    }
    if (key < parent.key) {
        assert(parent.left == nullptr);
        parent.connectReft(newNode);
    } else {
        assert(parent.right == nullptr);
        parent.connectRight(newNode);
    }
    balanceUpwards(newNode);TODO;
}

template <class T>
void AVLTree<T>::DestroyTree(std::shared_ptr<TreeNode<T>> &current)
{
    if (current == nullptr) {
        return;
    }
    std::shared_ptr<TreeNode<T>> left = current->left;
    if(left != nullptr) {
        left->top = nullptr;
        current->left = nullptr;
    }
    DestroyTree(left);
    std::shared_ptr<TreeNode<T>> right = current->right;
    if (right != nullptr) {
        right->top = nullptr;
        current->right = nullptr;
    }
    DestroyTree(right);
}

template <class T>
void AVLTree<T>::RollRight(TreeNode<T> &root)
{
    std::shared_ptr<TreeNode<T>> left = root->left;
    std::shared_ptr<TreeNode<T>> swing = left->right;
    root->connectReft(*swing);
    left->connectRight(*root);
    left.top = nullptr;
}

template <class T>
void AVLTree<T>::RollLeft(TreeNode<T> &root)
{
    TreeNode<T> right = root.right;
    TreeNode<T> swing = right.left;
    root.connectRight(swing);
    right.connectReft(root);
    right.top = nullptr;
}

template <class T>
TreeNode<T> AVLTree<T>::GetNode(int key)
{
    std::shared_ptr<TreeNode<T>> current = root;
    std::shared_ptr<TreeNode<T>> parent = current;
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
