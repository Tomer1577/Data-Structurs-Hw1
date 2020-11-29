#ifndef TWONODE_H
#define TWONODE_H

#include "TwoPair.h"
#include <memory>

struct TwoNode {
public:

    TwoPair data;
    std::shared_ptr<TwoNode> left;
    std::shared_ptr<TwoNode> right;

    TwoNode() = delete;
    TwoNode(int courseId, int classId) noexcept: data(courseId, classId), left(nullptr), right(nullptr) {}
    TwoNode(const TwoNode &other) = default;
    TwoNode& operator=(const TwoNode &other) = default;
    ~TwoNode() = default;

    bool operator==(const TwoNode &other) const
    {
        if (left != other.left) {
            return false;
        }
        if (right != other.right) {
            return false;
        }
        return data == other.data;
    }
};


#endif //TWONODE_H
