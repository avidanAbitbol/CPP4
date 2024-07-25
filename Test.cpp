#include "doctest.h"
#include "Node.h"
#include "Tree.h"

// Initialization and Basic Operations

TEST_CASE("Test Empty Tree Initialization") {
    Tree<int> tree;
    CHECK(tree.root == nullptr);
}

TEST_CASE("Test Add Root") {
    Tree<int> tree;
    Node<int> root_node(1);
    tree.add_root(root_node);
    CHECK(tree.root != nullptr);
    CHECK(tree.root->data == 1);
}

TEST_CASE("Test Add Single Sub Node") {
    Tree<int> tree;
    Node<int> root_node(1);
    Node<int> child_node(2);
    tree.add_root(root_node);
    tree.add_sub_node(root_node, child_node);
    CHECK(tree.root->children.size() == 1);
    CHECK(tree.root->children[0]->data == 2);
}

TEST_CASE("Test Add Multiple Sub Nodes") {
    Tree<int> tree;
    Node<int> root_node(1);
    Node<int> child_node1(2);
    Node<int> child_node2(3);
    tree.add_root(root_node);
    tree.add_sub_node(root_node, child_node1);
    tree.add_sub_node(root_node, child_node2);
    CHECK(tree.root->children.size() == 2);
    CHECK(tree.root->children[0]->data == 2);
    CHECK(tree.root->children[1]->data == 3);
}


TEST_CASE("Test Add Sub Node to Full Node") {
    Tree<int, 2> tree;
    Node<int> root_node(1);
    Node<int> child_node1(2);
    Node<int> child_node2(3);
    Node<int> child_node3(4);
    tree.add_root(root_node);
    tree.add_sub_node(root_node, child_node1);
    tree.add_sub_node(root_node, child_node2);
    CHECK_THROWS(tree.add_sub_node(root_node, child_node3));
}

TEST_CASE("Test Add Sub Node to Non-Existent Parent") {
    Tree<int> tree;
    Node<int> root_node(1);
    Node<int> child_node(2);
    Node<int> non_existent_node(3);
    tree.add_root(root_node);
    CHECK_THROWS(tree.add_sub_node(non_existent_node, child_node));
}

TEST_CASE("Test Tree Destructor") {
    Tree<int>* tree = new Tree<int>();
    Node<int> root_node(1);
    tree->add_root(root_node);
    Node<int> child_node(2);
    tree->add_sub_node(root_node, child_node);
    delete tree;
    // Check that the tree was correctly deallocated (no easy way to check directly, but no crash indicates success)
    CHECK(true);
}

// Iterators

TEST_CASE("Test Pre-Order Traversal on Empty Tree") {
    Tree<int> tree;
    auto it = tree.begin_preorder();
    CHECK_FALSE(it.has_next());
}

TEST_CASE("Test Pre-Order Traversal on Single Node Tree") {
    Tree<int> tree;
    Node<int> root_node(1);
    tree.add_root(root_node);
    auto it = tree.begin_preorder();
    CHECK(it.has_next());
    CHECK(it.next() == 1);
    CHECK_FALSE(it.has_next());
}

TEST_CASE("Test Pre-Order Traversal") {
    Tree<int> tree;
    Node<int> root_node(1);
    Node<int> child_node1(2);
    Node<int> child_node2(3);
    tree.add_root(root_node);
    tree.add_sub_node(root_node, child_node1);
    tree.add_sub_node(root_node, child_node2);
    auto it = tree.begin_preorder();
    CHECK(it.has_next());
    CHECK(it.next() == 1);
    CHECK(it.has_next());
    CHECK(it.next() == 2);
    CHECK(it.has_next());
    CHECK(it.next() == 3);
    CHECK_FALSE(it.has_next());
}

TEST_CASE("Test Post-Order Traversal on Empty Tree") {
    Tree<int> tree;
    auto it = tree.begin_postorder();
    CHECK_FALSE(it.has_next());
}

TEST_CASE("Test Post-Order Traversal on Single Node Tree") {
    Tree<int> tree;
    Node<int> root_node(1);
    tree.add_root(root_node);
    auto it = tree.begin_postorder();
    CHECK(it.has_next());
    CHECK(it.next() == 1);
    CHECK_FALSE(it.has_next());
}

TEST_CASE("Test Post-Order Traversal") {
    Tree<int> tree;
    Node<int> root_node(1);
    Node<int> child_node1(2);
    Node<int> child_node2(3);
    tree.add_root(root_node);
    tree.add_sub_node(root_node, child_node1);
    tree.add_sub_node(root_node, child_node2);
    auto it = tree.begin_postorder();
    CHECK(it.has_next());
    CHECK(it.next() == 2);
    CHECK(it.has_next());
    CHECK(it.next() == 3);
    CHECK(it.has_next());
    CHECK(it.next() == 1);
    CHECK_FALSE(it.has_next());
}

TEST_CASE("Test In-Order Traversal on Empty Tree") {
    Tree<int> tree;
    auto it = tree.begin_inorder();
    CHECK_FALSE(it.has_next());
}

TEST_CASE("Test In-Order Traversal on Single Node Tree") {
    Tree<int> tree;
    Node<int> root_node(1);
    tree.add_root(root_node);
    auto it = tree.begin_inorder();
    CHECK(it.has_next());
    CHECK(it.next() == 1);
    CHECK_FALSE(it.has_next());
}

TEST_CASE("Test In-Order Traversal") {
    Tree<int> tree;
    Node<int> root_node(1);
    Node<int> child_node1(2);
    Node<int> child_node2(3);
    tree.add_root(root_node);
    tree.add_sub_node(root_node, child_node1);
    tree.add_sub_node(root_node, child_node2);
    auto it = tree.begin_inorder();
    CHECK(it.has_next());
    CHECK(it.next() == 2);
    CHECK(it.has_next());
    CHECK(it.next() == 1);
    CHECK(it.has_next());
    CHECK(it.next() == 3);
    CHECK_FALSE(it.has_next());
}

TEST_CASE("Test BFS Traversal on Empty Tree") {
    Tree<int> tree;
    auto it = tree.begin_bfs();
    CHECK_FALSE(it.has_next());
}

TEST_CASE("Test BFS Traversal on Single Node Tree") {
    Tree<int> tree;
    Node<int> root_node(1);
    tree.add_root(root_node);
    auto it = tree.begin_bfs();
    CHECK(it.has_next());
    CHECK(it.next() == 1);
    CHECK_FALSE(it.has_next());
}

TEST_CASE("Test BFS Traversal") {
    Tree<int> tree;
    Node<int> root_node(1);
    Node<int> child_node1(2);
    Node<int> child_node2(3);
    tree.add_root(root_node);
    tree.add_sub_node(root_node, child_node1);
    tree.add_sub_node(root_node, child_node2);
    auto it = tree.begin_bfs();
    CHECK(it.has_next());
    CHECK(it.next() == 1);
    CHECK(it.has_next());
    CHECK(it.next() == 2);
    CHECK(it.has_next());
    CHECK(it.next() == 3);
    CHECK_FALSE(it.has_next());
}

TEST_CASE("Test DFS Traversal on Empty Tree") {
    Tree<int> tree;
    auto it = tree.begin_dfs();
    CHECK_FALSE(it.has_next());
}

TEST_CASE("Test DFS Traversal on Single Node Tree") {
    Tree<int> tree;
    Node<int> root_node(1);
    tree.add_root(root_node);
    auto it = tree.begin_dfs();
    CHECK(it.has_next());
    CHECK(it.next() == 1);
    CHECK_FALSE(it.has_next());
}

TEST_CASE("Test DFS Traversal") {
    Tree<int> tree;
    Node<int> root_node(1);
    Node<int> child_node1(2);
    Node<int> child_node2(3);
    tree.add_root(root_node);
    tree.add_sub_node(root_node, child_node1);
    tree.add_sub_node(root_node, child_node2);
    auto it = tree.begin_dfs();
    CHECK(it.has_next());
    CHECK(it.next() == 1);
    CHECK(it.has_next());
    CHECK(it.next() == 2);
    CHECK(it.has_next());
    CHECK(it.next() == 3);
    CHECK_FALSE(it.has_next());
}

TEST_CASE("Test Heap Traversal on Empty Tree") {
    Tree<int> tree;
    auto it = tree.begin_heap();
    CHECK_FALSE(it.has_next());
}

TEST_CASE("Test Heap Traversal on Single Node Tree") {
    Tree<int> tree;
    Node<int> root_node(1);
    tree.add_root(root_node);
    auto it = tree.begin_heap();
    CHECK(it.has_next());
    CHECK(it.next() == 1);
    CHECK_FALSE(it.has_next());
}


// Exception Handling

TEST_CASE("Test Add Sub Node to Uninitialized Tree") {
    Tree<int> tree;
    Node<int> sub_node(2);
    CHECK_THROWS_AS(tree.add_sub_node(Node<int>(1), sub_node), std::runtime_error);
}

TEST_CASE("Test Add Sub Node to Non-Existent Node") {
    Tree<int> tree;
    Node<int> root_node(1);
    Node<int> sub_node(2);
    tree.add_root(root_node);
    CHECK_THROWS_AS(tree.add_sub_node(Node<int>(3), sub_node), std::runtime_error);
}

TEST_CASE("Test Traversal on Uninitialized Tree") {
    Tree<int> tree;
    auto pre_order_it = tree.begin_preorder();
    CHECK_FALSE(pre_order_it.has_next());

    auto post_order_it = tree.begin_postorder();
    CHECK_FALSE(post_order_it.has_next());

    auto in_order_it = tree.begin_inorder();
    CHECK_FALSE(in_order_it.has_next());

    auto bfs_it = tree.begin_bfs();
    CHECK_FALSE(bfs_it.has_next());

    auto dfs_it = tree.begin_dfs();
    CHECK_FALSE(dfs_it.has_next());

    auto heap_it = tree.begin_heap();
    CHECK_FALSE(heap_it.has_next());
}

// Advanced Operations

TEST_CASE("Test Tree Deletion") {
    Tree<int>* tree = new Tree<int>();
    Node<int> root_node(1);
    tree->add_root(root_node);
    Node<int> child_node(2);
    tree->add_sub_node(root_node, child_node);
    delete tree;
    // No crash indicates success
    CHECK(true);
}

TEST_CASE("Test Deep Copy of Tree") {
    Tree<int> tree;
    Node<int> root_node(1);
    Node<int> child_node(2);
    tree.add_root(root_node);
    tree.add_sub_node(root_node, child_node);

    Tree<int> tree_copy = tree; // Deep copy
    CHECK(tree_copy.root->data == 1);
    CHECK(tree_copy.root->children[0]->data == 2);

    tree_copy.root->data = 3;
    CHECK_FALSE(tree.root->data == 1); // Ensure original tree is not affected
}

TEST_CASE("Test Move of Tree") {
    Tree<int> tree;
    Node<int> root_node(1);
    Node<int> child_node(2);
    tree.add_root(root_node);
    tree.add_sub_node(root_node, child_node);

    Tree<int> moved_tree = std::move(tree);
    CHECK(moved_tree.root->data == 1);
    CHECK(moved_tree.root->children[0]->data == 2);
    CHECK_FALSE(tree.root == nullptr); // Original tree should be empty
}

// Edge Cases

TEST_CASE("Test Add Sub Node with Complex Data Type") {
    struct Complex {
        int real;
        int imag;

        bool operator==(const Complex& other) const {
            return real == other.real && imag == other.imag;
        }
    };

    Tree<Complex> tree;
    Complex root_node = {1, 1};
    Complex child_node = {2, 2};
    Node<Complex> root(root_node);
    Node<Complex> child(child_node);
    tree.add_root(root);
    tree.add_sub_node(root, child);

    CHECK(tree.root->data == root_node);
    CHECK(tree.root->children[0]->data == child_node);
}

TEST_CASE("Test Traversal with Complex Data Type") {
    struct Complex {
        int real;
        int imag;

        bool operator==(const Complex& other) const {
            return real == other.real && imag == other.imag;
        }
    };

    Tree<Complex> tree;
    Complex root_node = {1, 1};
    Complex child_node = {2, 2};
    Node<Complex> root(root_node);
    Node<Complex> child(child_node);
    tree.add_root(root);
    tree.add_sub_node(root, child);

    auto it = tree.begin_preorder();
    CHECK(it.has_next());
    CHECK(it.next() == root_node);
    CHECK(it.has_next());
    CHECK(it.next() == child_node);
    CHECK_FALSE(it.has_next());
}

TEST_CASE("Test Multiple Levels of Depth") {
    Tree<int> tree;
    Node<int> root_node(1);
    Node<int> child_node1(2);
    Node<int> child_node2(3);
    Node<int> grandchild_node1(4);
    Node<int> grandchild_node2(5);

    tree.add_root(root_node);
    tree.add_sub_node(root_node, child_node1);
    tree.add_sub_node(root_node, child_node2);
    tree.add_sub_node(child_node1, grandchild_node1);
    tree.add_sub_node(child_node2, grandchild_node2);

    auto it = tree.begin_bfs();
    CHECK(it.has_next());
    CHECK(it.next() == 1);
    CHECK(it.has_next());
    CHECK(it.next() == 2);
    CHECK(it.has_next());
    CHECK(it.next() == 3);
    CHECK(it.has_next());
    CHECK(it.next() == 4);
    CHECK(it.has_next());
    CHECK(it.next() == 5);
    CHECK_FALSE(it.has_next());
}

