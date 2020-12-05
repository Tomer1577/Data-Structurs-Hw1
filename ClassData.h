#ifndef CLASSDATA_H
#define CLASSDATA_H

#include <memory>
#include "TwoNode.h"

struct ClassData {
    int numberOfViews;
    std::shared_ptr<TwoNode> pointer;

    ClassData() : numberOfViews(0), pointer(nullptr) {}
    ~ClassData() = default;
    ClassData& operator=(const ClassData& other) = default;
    ClassData(const ClassData& other) = default;
};


#endif //CLASSDATA_H
