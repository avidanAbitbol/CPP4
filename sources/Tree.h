#ifndef TREE_HPP
#define TREE_HPP

#include "Node.h"
#include <iostream>
#include <stdexcept>
#include <queue>
#include <stack>
#include <vector>
#include <memory>

/**
 * @brief A generic k-ary tree class.
 *
 * A k-ary tree is a tree in which each node has no more than k children.
 * The default value of k is 2, making it a binary tree by default.
 *
 * @tparam T The type of the data stored in the tree nodes.
 * @tparam N The maximum number of children each node can have. Default is 2.
 */
template<typename T, int N = 2>
class Tree {
public:
    std::shared_ptr<Node<T>> root;

    /**
     * @brief Default constructor.
     * Initializes an empty tree with no root.
     */
    Tree() : root(nullptr) {}

    /**
     * @brief Destructor.
     * Deletes the tree by deallocating all nodes.
     */
    ~Tree() {
        delete_tree(root);
    }

    /**
     * @brief Adds a root node to the tree.
     *
     * @param root_node The node to be added as the root.
     */
    void add_root(const Node<T> &root_node) {
        root = std::make_shared<Node<T>>(root_node.data);
    }

    /**
     * @brief Adds a sub-node to a parent node.
     *
     * @param parent_node The parent node to which the sub-node will be added.
     * @param sub_node The sub-node to be added.
     *
     * @throws std::runtime_error If the root node is not initialized.
     * @throws std::runtime_error If the parent node is not found.
     * @throws std::runtime_error If the parent node has reached the maximum number of children.
     */
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

    /**
     * @brief Prints the tree structure.
     *
     * This function prints the tree structure starting from the root.
     * Each level of the tree is indented to visually represent the tree hierarchy.
     */
    void print() const {
        printHelper(root, 0);
    }
    /**
      * @brief Returns a pre-order iterator starting at the root of the tree.
      *
      * @return PreOrderIterator An iterator for pre-order traversal.
      */
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
/**
     * @brief Returns a post-order iterator starting at the root of the tree.
     *
     * @return PostOrderIterator An iterator for post-order traversal.
     */
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
    /**
        * @brief Returns an in-order iterator starting at the root of the tree.
        *
        * @return InOrderIterator An iterator for in-order traversal.
        */
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
/**
     * @brief Returns a BFS iterator starting at the root of the tree.
     *
     * @return BFSIterator An iterator for breadth-first search traversal.
     */
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
/**
     * @brief Returns a DFS iterator starting at the root of the tree.
     *
     * @return DFSIterator An iterator for depth-first search traversal.
     */
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

    // Heap Iterator
    class HeapIterator {
    public:
        explicit HeapIterator(std::shared_ptr<Node<T>> root) {
            if (root) {
                nodes.push_back(root);
                build_min_heap();
            }
        }

        [[nodiscard]] bool has_next() const {
            return !nodes.empty();
        }

        T next() {
            if (!has_next()) throw std::out_of_range("No more elements");

            std::pop_heap(nodes.begin(), nodes.end(), node_compare);
            auto node = nodes.back();
            nodes.pop_back();
            return node->data;
        }

    private:
        std::vector<std::shared_ptr<Node<T>>> nodes;

        static bool node_compare(const std::shared_ptr<Node<T>> &a, const std::shared_ptr<Node<T>> &b) {
            return a->data > b->data;
        }

        void build_min_heap() {
            std::make_heap(nodes.begin(), nodes.end(), node_compare);
        }
    };

    PreOrderIterator begin_preorder() { return PreOrderIterator(root); }
    PostOrderIterator begin_postorder() { return PostOrderIterator(root); }
    InOrderIterator begin_inorder() { return InOrderIterator(root); }
    BFSIterator begin_bfs() { return BFSIterator(root); }
    DFSIterator begin_dfs() { return DFSIterator(root); }
    HeapIterator begin_heap() { return HeapIterator(root); }
    /**
        * @brief Finds a node with the given value starting from the specified node.
        *
        * @param node The node to start the search from.
        * @param value The value to search for.
        *
        * @return std::shared_ptr<Node<T>> A shared pointer to the found node, or nullptr if not found.
        */
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
    /**
        * @brief Helper function to print the tree structure.
        *
        * @param node The node to start printing from.
        * @param depth The current depth (used for indentation).
        */
    void printHelper(const std::shared_ptr<Node<T>> &node, int depth) const {
        if (!node) return;
        for (int i = 0; i < depth; ++i) std::cout << "  ";
        std::cout << node->data << std::endl;
        for (const auto &child : node->children) {
            printHelper(child, depth + 1);
        }
    }

    void delete_tree(const std::shared_ptr<Node<T>> &node) {
        if (!node) return;

        for (auto &child : node->children) {
            delete_tree(child);
        }
    }
};

#endif // TREE_HPP
