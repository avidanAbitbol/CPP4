#ifndef NODE_HPP
#define NODE_HPP

#include <memory>
#include <vector>

template<typename T>
class Node {

public:
    T data;
    int numOfChildren = 0;

    std::vector<std::shared_ptr<Node<T>>> children;

    explicit Node(T value) : data(value) {}

    void resize_children(int numChildren) {
        children.resize(static_cast<size_t>(numChildren), nullptr);
    };

    void set_data(T value) {
        data = value;
    }
};

#endif // NODE_HPP



//#ifndef NODE_HPP
//#define NODE_HPP
//
//#include <vector>
//#include <cstddef>
//
//template<typename T>
//class Node {
//public:
//    int numOfChildren = 0;
//    T data;
//    std::vector<Node<T> *> children;
//
//    explicit Node(T value) : data(value) {}
//
//    void add_child(Node<T> *child) {
//        children.push_back(child);
//    }
//
//    void resize_children(int numChildren) {
//        children.resize(static_cast<size_t>(numChildren), nullptr);
//    }
//
//    void set_data(T value) {
//        data = value;
//    }
//
//    ~Node() {
//        for (auto child: children) {
//            delete child;  // Delete each child node
//        }
//    }
//};
//
//#endif // NODE_HPP

