//
// Created by Eyal on 13/12/2020.
//

#ifndef NODE_H
#define NODE_H

#include <memory>

template <class T>
struct Node {
    T data;
    std::shared_ptr<Node<T>> left;
    std::shared_ptr<Node<T>> right;

    Node() = delete;
    explicit Node(const T& data): data(data), left(nullptr), right(nullptr) {}
    Node(const Node& other) = default;
    Node& operator=(const Node& other) = default;
    ~Node() = default;
};


#endif //NODE_H
