#ifndef NODE_HPP
#define NODE_HPP

#include <memory>
#include <vector>

/**
 * @brief This class represents a node in a tree data structure.
 *
 * @tparam T The data type of the elements stored in the tree nodes.
 */
template<typename T>
class Node {
public:
    T data; ///< The data stored in this node.
    int numOfChildren = 0; ///< The current number of children this node has.

    std::vector<std::shared_ptr<Node<T>>> children; ///< Dynamic array of shared pointers to the node's children.

    /**
     * @brief Construct a new Node object with the given data.
     *
     * @param value The data value to store in this node.
     */
    explicit Node(T value) : data(value) {}

    /**
     * @brief Resizes the children vector to a specified size and initializes them to nullptr.
     *
     * @param numChildren The new size of the children vector.
     */
    void resize_children(int numChildren) {
        children.resize(static_cast<size_t>(numChildren), nullptr);
    };

    /**
     * @brief Sets the data of this node.
     *
     * @param value The new data value for this node.
     */
    void set_data(T value) {
        data = value;
    }
};

#endif // NODE_HPP

