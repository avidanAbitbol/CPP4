/**
 * Demo app for Ex4
 */

#include <iostream>
#include "sources/Node.h"
#include "sources/Tree.h"
using namespace std;

int main() {

    Node<double> root_node = Node(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    Node<double> n1 = Node(1.2);
    Node<double> n2 = Node(1.3);
    Node<double> n3 = Node(1.4);
    Node<double> n4 = Node(1.5);
    Node<double> n5 = Node(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    std::cout << "Pre-Order Traversal: ";
    for (auto it = tree.begin_preorder(); it.has_next();) {
        std::cout << it.next() << " ";
    }
    std::cout << std::endl;

    std::cout << "Post-Order Traversal: ";
    for (auto it = tree.begin_postorder(); it.has_next();) {
        std::cout << it.next() << " ";  // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1
    }
    std::cout << std::endl;

    std::cout << "In-Order Traversal: ";
    for (auto it = tree.begin_inorder(); it.has_next();) {
        std::cout << it.next() << " "; // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3
    }
    std::cout << std::endl;

    std::cout << "BFS Traversal: ";
    for (auto it = tree.begin_bfs(); it.has_next();) {
        std::cout << it.next() << " ";
    }
    std::cout << std::endl;

    std::cout << "DFS Traversal: ";
    for (auto it = tree.begin_dfs(); it.has_next();) {
        std::cout << it.next() << " ";
    }
    std::cout << std::endl;

    // The tree should look like:
    /**
     *       root = 1.1
     *     /       \
     *    1.2      1.3
     *   /  \      /
     *  1.4  1.5  1.6
     */

    Tree<double, 3> three_ary_tree; // 3-ary tree.
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);

    // The tree should look like:
    /**
     *       root = 1.1
     *     /      |     \
     *    1.2    1.3    1.4
     *   /        |
     *  1.5      1.6
     */

    return 0;
}
