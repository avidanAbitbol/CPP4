//#ifndef TREE_HPP
//#define TREE_HPP
//
//#include "Node.h"
//#include <iostream>
//#include <stdexcept>
//#include <stack>
//#include <queue>
//
//template<typename T, int N = 2>
//class Tree {
//public:
//    std::shared_ptr<Node<T>> root;
//
//    Tree() : root(nullptr) {}
//
//    // Destructor
//    ~Tree() {
//        // Call recursive function to delete all nodes starting from root
//        if (root) {
//            delete_tree(root);
//        }
//    }
//
//    // Other methods (add_root, add_sub_node, etc.) here
//
//
//
//    void add_root(const Node<T> &root_node) {
//        root = std::make_shared<Node<T>>(root_node.data);
//    }
//
//    void add_sub_node(const Node<T> &parent_node, Node<T> &sub_node) {
//        if (!root) {
//            throw std::runtime_error("Root node is not initialized.");
//        }
//
//        auto parent = find_node(root, parent_node.data);
//        if (!parent) {
//            throw std::runtime_error("Parent node not found.");
//        }
//
//
//        // Ensure sub_node has N children available
//        sub_node.resize_children(N);
//
//        // Convert sub_node to a shared_ptr
//        auto new_node = std::make_shared<Node<T>>(sub_node.data);
//        new_node->children = std::move(sub_node.children); // Move the children to the new node
//
//        // Check if there's an available slot in parent's children
//        if (parent->numOfChildren == N) {
//            throw std::runtime_error("Parent node has reached maximum number of children.");
//        } else {
//            parent->children.push_back(new_node);
//            parent->numOfChildren++;
//        }
//    }
//
//
//    void print() const {
//        printHelper(root, 0);
//    }
//
//    // Pre-Order Iterator for binary trees and DFS for general trees
//    class PreOrderIterator {
//    public:
//        PreOrderIterator(std::shared_ptr<Node<T>> root) {
//            if (root) {
//                stack.push(root);
//            }
//        }
//
//        bool has_next() const {
//            return !stack.empty();
//        }
//
//        T next() {
//            if (!has_next()) throw std::out_of_range("No more elements");
//
//            auto node = stack.top();
//            stack.pop();
//
//            // Push right child first so left is processed first
//            for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
//                if (*it) stack.push(*it);
//            }
//
//            return node->data;
//        }
//
//    private:
//        std::stack<std::shared_ptr<Node<T>>> stack;
//    };
//
//    // Post-Order Iterator for binary trees and DFS for general trees
//    class PostOrderIterator {
//    public:
//        PostOrderIterator(std::shared_ptr<Node<T>> root) {
//            push_leftmost(root);
//        }
//
//        bool has_next() const {
//            return !stack.empty();
//        }
//
//        T next() {
//            if (!has_next()) throw std::out_of_range("No more elements");
//
//            auto node = stack.top();
//            stack.pop();
//
//            if (!stack.empty() && node == stack.top()->children.back()) {
//                auto parent = stack.top();
//                stack.pop();
//                push_leftmost(parent);
//                stack.push(parent);
//            }
//
//            return node->data;
//        }
//
//    private:
//        std::stack<std::shared_ptr<Node<T>>> stack;
//
//        void push_leftmost(std::shared_ptr<Node<T>> node) {
//            while (node) {
//                stack.push(node);
//                if (!node->children.empty()) {
//                    node = node->children.front();
//                } else {
//                    node = nullptr;
//                }
//            }
//        }
//    };
//
//    // In-Order Iterator for binary trees and DFS for general trees
//    class InOrderIterator {
//    public:
//        InOrderIterator(std::shared_ptr<Node<T>> root) {
//            push_leftmost(root);
//        }
//
//        bool has_next() const {
//            return !stack.empty();
//        }
//
//        T next() {
//            if (!has_next()) throw std::out_of_range("No more elements");
//
//            auto node = stack.top();
//            stack.pop();
//
//            if (!node->children.empty() && node->children.size() > 1) {
//                push_leftmost(node->children[1]);
//            }
//
//            return node->data;
//        }
//
//    private:
//        std::stack<std::shared_ptr<Node<T>>> stack;
//
//        void push_leftmost(std::shared_ptr<Node<T>> node) {
//            while (node) {
//                stack.push(node);
//                if (!node->children.empty()) {
//                    node = node->children.front();
//                } else {
//                    node = nullptr;
//                }
//            }
//        }
//    };
//
//    // BFS Iterator
//    class BFSIterator {
//    public:
//        BFSIterator(std::shared_ptr<Node<T>> root) {
//            if (root) {
//                queue.push(root);
//            }
//        }
//
//        bool has_next() const {
//            return !queue.empty();
//        }
//
//        T next() {
//            if (!has_next()) throw std::out_of_range("No more elements");
//
//            auto node = queue.front();
//            queue.pop();
//
//            for (auto &child: node->children) {
//                if (child) queue.push(child);
//            }
//
//            return node->data;
//        }
//
//    private:
//        std::queue<std::shared_ptr<Node<T>>> queue;
//    };
//
//    // DFS Iterator
//    class DFSIterator {
//    public:
//        DFSIterator(std::shared_ptr<Node<T>> root) {
//            if (root) {
//                stack.push(root);
//            }
//        }
//
//        bool has_next() const {
//            return !stack.empty();
//        }
//
//        T next() {
//            if (!has_next()) throw std::out_of_range("No more elements");
//
//            auto node = stack.top();
//            stack.pop();
//
//            for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
//                if (*it) stack.push(*it);
//            }
//
//            return node->data;
//        }
//
//    private:
//        std::stack<std::shared_ptr<Node<T>>> stack;
//    };
//
//    PreOrderIterator begin_preorder() { return PreOrderIterator(root); }
//    PostOrderIterator begin_postorder() { return PostOrderIterator(root); }
//    InOrderIterator begin_inorder() { return InOrderIterator(root); }
//    BFSIterator begin_bfs() { return BFSIterator(root); }
//    DFSIterator begin_dfs() { return DFSIterator(root); }
//
//private:
//    std::shared_ptr<Node<T>> find_node(const std::shared_ptr<Node<T>> &node, const T &value) const {
//        if (!node) return nullptr;
//        if (node->data == value) return node;
//        for (const auto &child: node->children) {
//            auto found = find_node(child, value);
//            if (found) return found;
//        }
//        return nullptr;
//    }
//
//    void printHelper(const std::shared_ptr<Node<T>> &node, int depth) const {
//        if (!node) return;
//        for (int i = 0; i < depth; ++i) std::cout << "  ";
//        std::cout << node->data << std::endl;
//        for (const auto &child: node->children) {
//            printHelper(child, depth + 1);
//        }
//    }
//
//    // Recursive function to delete all nodes in the tree
//    void delete_tree(std::shared_ptr<Node<T>> node) {
//        if (!node) {
//            return;
//        }
//
//        // Recursively delete children
//        for (auto &child: node->children) {
//            delete_tree(child);
//        }
//
//        // Automatically releases the memory held by 'node'
//        // when 'node' goes out of scope
//    }
//};
//
//#endif // TREE_HPP
//
//
//
//



#ifndef TREE_HPP
#define TREE_HPP

#include "Node.h"
#include <iostream>
#include <stdexcept>
#include <queue>
#include <stack>
#include <vector>
#include <memory>

template<typename T, int N = 2>
class Tree {
public:
    std::shared_ptr<Node<T>> root;

    Tree() : root(nullptr) {}

    // Destructor
    ~Tree() {
        if (root) {
            delete_tree(root);
        }
    }

    void add_root(const Node<T> &root_node) {
        root = std::make_shared<Node<T>>(root_node.data);
    }

    void add_sub_node(const Node<T> &parent_node, Node<T> &sub_node) {
        if (!root) {
            throw std::runtime_error("Root node is not initialized.");
        }

        auto parent = find_node(root, parent_node.data);
        if (!parent) {
            throw std::runtime_error("Parent node not found.");
        }

        sub_node.resize_children(N);

        auto new_node = std::make_shared<Node<T>>(sub_node.data);
        new_node->children = std::move(sub_node.children);

        if (parent->numOfChildren == N) {
            throw std::runtime_error("Parent node has reached maximum number of children.");
        } else {
            parent->children.push_back(new_node);
            parent->numOfChildren++;
        }
    }

    void print() const {
        printHelper(root, 0);
    }

    class PreOrderIterator {
    public:
        explicit PreOrderIterator(std::shared_ptr<Node<T>> root) {
            if (root) {
                stack.push(root);
            }
        }

        [[nodiscard]] bool has_next() const {
            return !stack.empty();
        }

        T next() {
            if (!has_next()) throw std::out_of_range("No more elements");

            auto node = stack.top();
            stack.pop();

            for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                if (*it) stack.push(*it);
            }

            return node->data;
        }

    private:
        std::stack<std::shared_ptr<Node<T>>> stack;
    };

    class PostOrderIterator {
    public:
        explicit PostOrderIterator(std::shared_ptr<Node<T>> root) {
            if (root) {
                add_nodes(root);
            }
        }

        [[nodiscard]] bool has_next() const {
            return !queue.empty();
        }

        T next() {
            if (!has_next()) throw std::out_of_range("No more elements");

            auto node = queue.front();
            queue.pop();
            return node->data;
        }

    private:
        std::queue<std::shared_ptr<Node<T>>> queue;

        void add_nodes(const std::shared_ptr<Node<T>> &node) {
            if (!node) return;

            for (const auto &child : node->children) {
                add_nodes(child);
            }
            queue.push(node);
        }
    };

    class InOrderIterator {
    public:
        explicit InOrderIterator(std::shared_ptr<Node<T>> root) {
            add_nodes(root);
        }

        [[nodiscard]] bool has_next() const {
            return !nodes.empty();
        }

        T next() {
            if (!has_next()) throw std::out_of_range("No more elements");

            auto node = nodes.front();
            nodes.erase(nodes.begin());
            return node->data;
        }

    private:
        std::vector<std::shared_ptr<Node<T>>> nodes;

        void add_nodes(const std::shared_ptr<Node<T>> &node) {
            if (!node) return;

            if (!node->children.empty()) {
                add_nodes(node->children[0]);
            }

            nodes.push_back(node);

            if (node->children.size() > 1) {
                for (size_t i = 1; i < node->children.size(); ++i) {
                    add_nodes(node->children[i]);
                }
            }
        }
    };

    class BFSIterator {
    public:
        explicit BFSIterator(std::shared_ptr<Node<T>> root) {
            if (root) {
                queue.push(root);
            }
        }

        [[nodiscard]] bool has_next() const {
            return !queue.empty();
        }

        T next() {
            if (!has_next()) throw std::out_of_range("No more elements");

            auto node = queue.front();
            queue.pop();

            for (auto &child : node->children) {
                if (child) queue.push(child);
            }

            return node->data;
        }

    private:
        std::queue<std::shared_ptr<Node<T>>> queue;
    };

    class DFSIterator {
    public:
        explicit DFSIterator(std::shared_ptr<Node<T>> root) {
            if (root) {
                stack.push(root);
            }
        }

        [[nodiscard]] bool has_next() const {
            return !stack.empty();
        }

        T next() {
            if (!has_next()) throw std::out_of_range("No more elements");

            auto node = stack.top();
            stack.pop();

            for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                if (*it) stack.push(*it);
            }

            return node->data;
        }

    private:
        std::stack<std::shared_ptr<Node<T>>> stack;
    };

    PreOrderIterator begin_preorder() { return PreOrderIterator(root); }
    PostOrderIterator begin_postorder() { return PostOrderIterator(root); }
    InOrderIterator begin_inorder() { return InOrderIterator(root); }
    BFSIterator begin_bfs() { return BFSIterator(root); }
    DFSIterator begin_dfs() { return DFSIterator(root); }

private:
    std::shared_ptr<Node<T>> find_node(const std::shared_ptr<Node<T>> &node, const T &value) const {
        if (!node) return nullptr;
        if (node->data == value) return node;
        for (const auto &child : node->children) {
            auto found = find_node(child, value);
            if (found) return found;
        }
        return nullptr;
    }

    void printHelper(const std::shared_ptr<Node<T>> &node, int depth) const {
        if (!node) return;
        for (int i = 0; i < depth; ++i) std::cout << "  ";
        std::cout << node->data << std::endl;
        for (const auto &child : node->children) {
            printHelper(child, depth + 1);
        }
    }

    void delete_tree(std::shared_ptr<Node<T>> node) {
        if (!node) {
            return;
        }

        for (auto &child : node->children) {
            delete_tree(child);
        }
    }
};

#endif // TREE_HPP
