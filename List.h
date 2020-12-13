#ifndef LIST_H
#define LIST_H

#include "Node.h"
#include <memory>

template <class T>
class List {
private:
    std::shared_ptr<Node<T>> first;
    std::shared_ptr<Node<T>> last;

public:
    List(): first(new Node<T>(T())), last(new Node<T>(T()))
    {
        first->right = last;
        last->left = first;
    }
    List(const List &other): first(new Node<T>(T())), last(new Node<T>(T()))
    {
        first->right = last;
        last->left = first;
        for (const T& item:other) {
            PushRear(item);
        }
    }
    List& operator=(const List &other)
    {
        if (this != &other) {
            std::shared_ptr<Node<T>> newFirst(new Node<T>(T()));
            std::shared_ptr<Node<T>> newLast(new Node<T>(T()));
            for (const T& item:other) {
                std::shared_ptr<Node<T>> newNode(new Node<T>(item));
                newNode->left = last->left;
                last->left = newNode;
                newNode->right = last;
                newNode->left->right = newNode;
            }
        }
        return *this;
    }
    ~List()
    {
        while(first->right != nullptr) {
            first->right->left = nullptr;
            std::shared_ptr<Node<T>> temp = first->right;
            first->right = nullptr;
            first = temp;
        }
        first = nullptr;
        last = nullptr;
    }


    void PushFront(const T& data);
    void PushRear(const T& data);
    void PopFront();
    void PopRear();

    T& Front() {
        return first->right->data;
    }

    T& Rear() {
        return last->left->data;
    }

    bool IsEmpty() {
        return first->right == last;
    }

    class iterator;
    iterator begin()
    {
        return iterator(first->right);
    }
    iterator end()
    {
        return iterator(last);
    }
    class const_iterator;
    const_iterator begin() const
    {
        return const_iterator(first->right);
    }
    const_iterator end() const
    {
        return const_iterator(last);
    }
};

template <class T>
class List<T>::iterator  {
private:
    friend class List<T>;

    std::shared_ptr<Node<T>> current;
    explicit iterator(std::shared_ptr<Node<T>> current): current(current) {}

public:
    iterator() = delete;
    iterator(const iterator& other) = default;
    iterator& operator=(const iterator& other) = default;
    ~iterator() = default;

    T& operator*() {
        return current->data;
    }

    iterator& operator++()
    {
        current = current->left;
        return *this;
    }
    iterator operator++(int)
    {
        iterator copy(*this);
        ++this;
        return copy;
    }

    bool operator==(const iterator& other)
    {
        return current == other.current;
    }
    bool operator!=(const iterator& other)
    {
        return current == other.current;
    }
};

template <class T>
class List<T>::const_iterator  {
private:
    friend class List<T>;

    std::shared_ptr<Node<T>> current;
    explicit const_iterator(std::shared_ptr<Node<T>> current): current(current) {}

public:
    const_iterator() = delete;
    const_iterator(const const_iterator& other) = default;
    const_iterator& operator=(const const_iterator& other) = default;
    ~const_iterator() = default;

    const T& operator*() {
        return current->data;
    }

    const_iterator& operator++()
    {
        current = current->left;
        return *this;
    }
    const_iterator operator++(int)
    {
        iterator copy(*this);
        ++this;
        return copy;
    }

    bool operator==(const const_iterator& other)
    {
        return current == other.current;
    }
    bool operator!=(const const_iterator& other)
    {
        return current == other.current;
    }
};

template <class T>
void List<T>::PushFront(const T& data)
{
    std::shared_ptr<Node<T>> newNode(new Node<T>(data));
    newNode->right = first->right;
    first->right = newNode;
    newNode->left = first;
    newNode->right->left = newNode;
}

template <class T>
void List<T>::PushRear(const T& data)
{
    std::shared_ptr<Node<T>> newNode(new Node<T>(data));
    newNode->left = last->left;
    last->left = newNode;
    newNode->right = last;
    newNode->left->right = newNode;
}

template<class T>
void List<T>::PopFront()
{
    if (IsEmpty()) {
        return;
    }
    std::shared_ptr<Node<T>> temp = first->right;
    first->right = first->right->right;
    first->right->left = first;
    temp->left = nullptr;
    temp->right = nullptr;
}

template<class T>
void List<T>::PopRear()
{
    if (IsEmpty()) {
        return;
    }
    std::shared_ptr<Node<T>> temp = last->left;
    last->left = last->left->left;
    last->left->right = last;
    temp->left = nullptr;
    temp->right = nullptr;
}

#endif //LIST_H
