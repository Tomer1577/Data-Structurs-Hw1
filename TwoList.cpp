#include "TwoList.h"
#include "TwoPair.h"


TwoList::TwoList(const TwoList& other): first(nullptr), last(nullptr)
{
    for (const TwoNode& node:other) {
        PushBack(node.data.courseId, node.data.classId);
    }
}

TwoList& TwoList::operator=(const TwoList& other)
{
    if(this != &other) {
        std::shared_ptr<TwoNode> previous = nullptr;
        std::shared_ptr<TwoNode> newFirst = nullptr;
        for (const TwoNode& node:other) {
            TwoNode next(node.data.courseId, node.data.classId);
            if (previous == nullptr) {
                previous = std::shared_ptr<TwoNode>(&next);
                newFirst = previous;
            } else {
                previous->right = std::shared_ptr<TwoNode>(&next);
                next.left = previous;
                previous = previous->right;
            }
        }

        DestroyList(first);
        first = newFirst;
        last = previous;
    }
    return *this;
}

TwoList::~TwoList()
{
    last = nullptr;
    DestroyList(first);
    first = nullptr;
}

std::shared_ptr<TwoNode> TwoList::PushFront(int courseId, int classId)
{
    if (first == nullptr) {
        assert(last == nullptr);
        first = std::shared_ptr<TwoNode>(new TwoNode(courseId, classId));
        last = first;
        return first;
    } else {
        assert(last != nullptr && first->left == nullptr);
        first->left = std::shared_ptr<TwoNode>(new TwoNode(courseId, classId));
        first->left->right = first;
        first = first->left;
        return first;
    }
}

std::shared_ptr<TwoNode> TwoList::PushBack(int courseId, int classId)
{
    if (last == nullptr) {
        assert(first == nullptr);
        last = std::shared_ptr<TwoNode>(new TwoNode(courseId, classId));
        first = last;
        return last;
    } else {
        assert(first != nullptr && last->right == nullptr);
        last->right = std::shared_ptr<TwoNode>(new TwoNode(courseId, classId));
        last->right->left = last;
        last = last->right;
        return last;
    }
}

void TwoList::PopPtr(const std::shared_ptr<TwoNode>& ptr)
{
    assert(ptr != nullptr);
    assert(IsInList(ptr));
    bool isFirst = true;
    bool isLast = true;

    if (ptr->left != nullptr) {
        assert(ptr != first);
        isFirst = false;
        ptr->left->right = ptr->right;
    }
    if (ptr->right != nullptr) {
        assert(ptr != last);
        isLast = false;
        ptr->right->left = ptr->left;
    }

    if(isFirst) {
        first = first->right;
    }
    if(isLast) {
        last = last->left;
    }
}

void TwoList::PopFront()
{
    if (first == nullptr) {
        return;
    }
    if (first == last) {
        first = nullptr;
        last = nullptr;
        return;
    }
    first = first->right;
    first->left->right = nullptr;
    first->left = nullptr;
}

void TwoList::PopBack()
{
    if (last == nullptr) {
        return;
    }
    if (first == last) {
        first = nullptr;
        last = nullptr;
        return;
    }
    last = last->left;
    last->right->left = nullptr;
    last->right = nullptr;
}

TwoList::iterator TwoList::begin()
{
    return iterator(first);
}

TwoList::iterator TwoList::end()
{
    return iterator(nullptr);
}

TwoList::const_iterator TwoList::begin () const
{
    return const_iterator(first);
}

TwoList::const_iterator TwoList::end () const
{
    return const_iterator(nullptr);
}

bool TwoList::IsInList(const std::shared_ptr<TwoNode> &ptr) const
{
    for (const TwoNode& node:(*this)) {
        if (&node == ptr.get()) {
            return true;
        }
    }
    return false;
}

void TwoList::DestroyList(std::shared_ptr<TwoNode> &start) noexcept
{
    while(start != nullptr) {
        TwoNode temp = *start;
        start = temp.right;
        temp.left = nullptr;
        temp.right = nullptr;
    }
}
