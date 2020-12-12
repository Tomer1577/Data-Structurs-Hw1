#ifndef TREENODE_H
#define TREENODE_H

#define NULL_HEIGHT -1

#include <memory>

template <class S, class T>
struct TreeNode {
public:

    S key;
    T data;
    std::shared_ptr<TreeNode> top;
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;
    int height;

    TreeNode() = delete;
    explicit TreeNode(const S &key, const T &data) noexcept:
        key(key), data(data), top(nullptr), left(nullptr), right(nullptr), height(0) {}
    TreeNode(const TreeNode &other) = default;
    TreeNode& operator=(const TreeNode &other) = default;
    ~TreeNode() = default;

    bool operator==(const TreeNode &other) const
    {
        return key==other.key;
    }
    bool operator<=(const TreeNode &other) const
    {
        return key<=other.key;
    }
    bool operator>=(const TreeNode &other) const
    {
        return key>=other.key;
    }
    bool operator<(const TreeNode &other) const
    {
        return key<other.key;
    }
    bool operator>(const TreeNode &other) const
    {
        return key>other.key;
    }

    void update_height() {
        int leftHeight = (left == nullptr)? NULL_HEIGHT : left->height;
        int rightHeight = (right == nullptr)? NULL_HEIGHT : right->height;
        height = leftHeight>rightHeight? 1 + leftHeight : 1 + rightHeight;
    }
    int balanceFactor()
    {
        int leftHeight = (left == nullptr)? NULL_HEIGHT : left->height;
        int rightHeight = (right == nullptr)? NULL_HEIGHT : right->height;
        return leftHeight-rightHeight;
    }
};


#endif //TREENODE_H
