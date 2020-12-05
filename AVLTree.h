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

    T& GetItem(const S &key);
    void Insert(const S &key, const T &data);//this needs to be AVLtree type no to return the nrew tree no?
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

template <class S, class T>
T& AVLTree<S,T>::GetItem(const S &key)
{
    return GetNode(key).data;
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
void AVLTree<S,T>::Remove(const S &key)//needs to be type AVLTree i think
//the plan is to add back the small one and go down the small one untill i find a place absolute worst time for that time is log n i think
//then start balance from the connected one
{
    TreeNode<S,T> to_remove = GetNode(key);
    if(to_remove.key != key)
    {
        //throw no such node
        //for now:
        return;
    }
    std::shared_ptr<TreeNode<S,T>> parent = to_remove.top;
    std::shared_ptr<TreeNode<S,T>> left = to_remove.left;
    std::shared_ptr<TreeNode<S,T>> right = to_remove.right;
    bool side = (parent -> right).key  == key;//should test this works!!
    if (left == nullptr && right == nullptr)
    {
        balanceUpwards(parent);
        std::shared_ptr<TreeNode<S,T>> to_free = side? *(parent).right : *(parent).left;
        delete(to_free);//is this how you do it ? do i need to put null where i freed???
        return;
    }

    TreeNode<S,T> current = side ? *left : *right;//start with the opposite side
    if(current != nullptr)
    {
        std::shared_ptr<TreeNode<S,T>> current_side = side ? current.right : current.left;
        while(current_side != nullptr)
        {
            current = *(current_side);
            current_side = side ? current.right : current.left;
        }
    }
    if(side)//add combin original children to one.
    {
        current.right = right;
        int leftHeight = (left == nullptr)? NULL_HEIGHT : left->height;
        current.height = leftHeight>(right -> hight) ? leftHeight : (right -> hight);
    }
    else
    {
        current.left = left;   
        int rightHeight = (right == nullptr)? NULL_HEIGHT : right->height;
        current.height = rightHeight>(left -> hight) ? rightHeight : (left -> hight);
    }

    std::shared_ptr<TreeNode<S,T>> to_free = side? *(parent).right : *(parent).left;
    if(side)
    {
        *(parent).right = left;
    }
    else
    {
        *(parent).left = right;   
    }
    delete(to_free);//is this how you do it ?
    balanceUpwards(current);
    return;
}
#endif //AVLTREE_H
