#ifndef TWOLIST_H
#define TWOLIST_H

#include <cassert>
#include <memory>
#include "TwoNode.h"

class TwoList {
private:

    std::shared_ptr<TwoNode> first;
    std::shared_ptr<TwoNode> last;

    bool IsInList(const std::shared_ptr<TwoNode> &ptr) const;
    static void DestroyList(std::shared_ptr<TwoNode> &start) noexcept;

public:

    TwoList(): first(nullptr), last(nullptr) {}
    TwoList(const TwoList &other);
    TwoList& operator=(const TwoList &other);
    ~TwoList();

    std::shared_ptr<TwoNode> PushFront(int courseId, int classId);
    std::shared_ptr<TwoNode> PushBack(int courseId, int classId);

    void PopPtr(const std::shared_ptr<TwoNode>& ptr);
    void PopFront();
    void PopBack();

    class iterator;
    iterator begin();
    iterator end();
    class const_iterator;
    const_iterator begin() const;
    const_iterator end() const;
};

class TwoList::iterator {
private:

    std::shared_ptr<TwoNode> ptr;

    explicit iterator(const std::shared_ptr<TwoNode>& ptr): ptr(ptr) {}

    friend class TwoList;

public:

    iterator() = delete;
    iterator(const iterator &other) = default;
    iterator& operator=(const iterator &other)  = default;
    ~iterator() = default;

    TwoNode& operator*() const
    {
        assert(ptr != nullptr);
        return *ptr;
    }
    iterator& operator++()
    {
        assert(ptr != nullptr);
        ptr = ptr->right;
        return *this;
    }
    iterator operator++(int)
    {
        assert(ptr != nullptr);
        iterator copy = *this;
        ptr = ptr->right;
        return copy;
    }

    bool operator==(const iterator& other)
    {
        return ptr==other.ptr;
    }
    bool operator!=(const iterator& other)
    {
        return ptr!=other.ptr;
    }
};

class TwoList::const_iterator {
private:

    std::shared_ptr<TwoNode> ptr;

    explicit const_iterator(const std::shared_ptr<TwoNode>& ptr): ptr(ptr) {}

    friend class TwoList;

public:

    const_iterator() = delete;
    const_iterator(const const_iterator &other) = default;
    const_iterator& operator=(const const_iterator &other)  = default;
    ~const_iterator() = default;

    const TwoNode& operator*() const
    {
        assert(ptr != nullptr);
        return *ptr;
    }
    const_iterator& operator++()
    {
        assert(ptr != nullptr);
        ptr = ptr->right;
        return *this;
    }
    const_iterator operator++(int)
    {
        assert(ptr != nullptr);
        const_iterator copy = *this;
        ptr = ptr->right;
        return copy;
    }

    bool operator==(const const_iterator& other)
    {
        return ptr==other.ptr;
    }
    bool operator!=(const const_iterator& other)
    {
        return ptr!=other.ptr;
    }
};

#endif //TWOLIST_H
