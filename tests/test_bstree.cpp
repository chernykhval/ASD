// Copyright 2026 Chernykh Valentin

#define EPSILON 0.000001

#include <gtest/gtest.h>
#include "libs/lib_bstree/bstree.h"

TEST(TestBSTree, BSTreeSortArray) {
    BSTree<int, int> tree;

    int array[10] = {10, 3, 7, 8, 9, 4, 1, 2, 6, 5};

    for (int i = 0; i < 10; i++) {
        tree.insert(array[i], i);
    }

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_dlcr();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "1:6, 2:7, 3:1, 4:5, 5:9, 6:8, 7:2, 8:3, 9:4, 10:0\n");
}

TEST(TestBSTree, BSTreeErase) {
    BSTree<int, int> tree;

    int array[10] = {5, 3, 1, 2, 4, 7, 9, 10, 8, 6};

    for (int i = 0; i < 10; i++) {
        tree.insert(array[i], i);
    }

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "    10:7\n"
                        "   9:6\n"
                        "    8:8\n"
                        "  7:5\n"
                        "   6:9\n"
                        " 5:0\n"
                        "   4:4\n"
                        "  3:1\n"
                        "    2:3\n"
                        "   1:2\n");

    tree.erase(3);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "    10:7\n"
                        "   9:6\n"
                        "    8:8\n"
                        "  7:5\n"
                        "   6:9\n"
                        " 5:0\n"
                        "   4:4\n"
                        "  2:3\n"
                        "   1:2\n");
}

TEST(TestBSTree, BSTreeEraseLeaf) {
    BSTree<int, int> tree;

    int array[11] = {6, 4, 7, 1, 5, 11, 2, 9, 3, 8, 10};

    for (int i = 0; i < 11; i++) {
        tree.insert(array[i], i);
    }

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "   11:5\n"
                        "     10:10\n"
                        "    9:7\n"
                        "     8:9\n"
                        "  7:2\n"
                        " 6:0\n"
                        "   5:4\n"
                        "  4:1\n"
                        "     3:8\n"
                        "    2:6\n"
                        "   1:3\n");

    tree.erase(3);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "   11:5\n"
                        "     10:10\n"
                        "    9:7\n"
                        "     8:9\n"
                        "  7:2\n"
                        " 6:0\n"
                        "   5:4\n"
                        "  4:1\n"
                        "    2:6\n"
                        "   1:3\n");
}

TEST(TestBSTree, BSTreeEraseNodeWithOneLeftChild) {
    BSTree<int, int> tree;

    int array[11] = {6, 4, 7, 1, 5, 11, 2, 9, 3, 8, 10};

    for (int i = 0; i < 11; i++) {
        tree.insert(array[i], i);
    }

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "   11:5\n"
                        "     10:10\n"
                        "    9:7\n"
                        "     8:9\n"
                        "  7:2\n"
                        " 6:0\n"
                        "   5:4\n"
                        "  4:1\n"
                        "     3:8\n"
                        "    2:6\n"
                        "   1:3\n");

    tree.erase(11);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "   10:10\n"
                        "    9:7\n"
                        "     8:9\n"
                        "  7:2\n"
                        " 6:0\n"
                        "   5:4\n"
                        "  4:1\n"
                        "     3:8\n"
                        "    2:6\n"
                        "   1:3\n");
}

TEST(TestBSTree, BSTreeEraseNodeWithOneRightChild) {
    BSTree<int, int> tree;

    int array[11] = {6, 4, 7, 1, 5, 11, 2, 9, 3, 8, 10};

    for (int i = 0; i < 11; i++) {
        tree.insert(array[i], i);
    }

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "   11:5\n"
                        "     10:10\n"
                        "    9:7\n"
                        "     8:9\n"
                        "  7:2\n"
                        " 6:0\n"
                        "   5:4\n"
                        "  4:1\n"
                        "     3:8\n"
                        "    2:6\n"
                        "   1:3\n");

    tree.erase(7);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "   11:5\n"
                        "     10:10\n"
                        "    9:7\n"
                        "  8:9\n"
                        " 6:0\n"
                        "   5:4\n"
                        "  4:1\n"
                        "     3:8\n"
                        "    2:6\n"
                        "   1:3\n");
}

TEST(TestBSTree, BSTreeEraseRootNode) {
    BSTree<int, int> tree;

    int array[11] = {6, 4, 7, 1, 5, 11, 2, 9, 3, 8, 10};

    for (int i = 0; i < 11; i++) {
        tree.insert(array[i], i);
    }

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "   11:5\n"
                        "     10:10\n"
                        "    9:7\n"
                        "     8:9\n"
                        "  7:2\n"
                        " 6:0\n"
                        "   5:4\n"
                        "  4:1\n"
                        "     3:8\n"
                        "    2:6\n"
                        "   1:3\n");

    tree.erase(6);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "   11:5\n"
                        "     10:10\n"
                        "    9:7\n"
                        "     8:9\n"
                        "  7:2\n"
                        " 5:4\n"
                        "  4:1\n"
                        "     3:8\n"
                        "    2:6\n"
                        "   1:3\n");
}

TEST(TestBSTree, BSTreeEraseNoodWithTwoChields) {
    BSTree<int, int> tree;

    int array[11] = {6, 4, 7, 1, 5, 11, 2, 9, 3, 8, 10};

    for (int i = 0; i < 11; i++) {
        tree.insert(array[i], i);
    }

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "   11:5\n"
                        "     10:10\n"
                        "    9:7\n"
                        "     8:9\n"
                        "  7:2\n"
                        " 6:0\n"
                        "   5:4\n"
                        "  4:1\n"
                        "     3:8\n"
                        "    2:6\n"
                        "   1:3\n");

    tree.erase(9);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "   11:5\n"
                        "     10:10\n"
                        "    8:9\n"
                        "  7:2\n"
                        " 6:0\n"
                        "   5:4\n"
                        "  4:1\n"
                        "     3:8\n"
                        "    2:6\n"
                        "   1:3\n");
}

TEST(TestBSTree, BSTreeEraseKeyNotExistThrow) {
    BSTree<int, int> tree;

    int array[11] = {6, 4, 7, 1, 5, 11, 2, 9, 3, 8, 10};

    for (int i = 0; i < 11; i++) {
        tree.insert(array[i], i);
    }

    EXPECT_THROW(tree.erase(25), std::invalid_argument);
}

TEST(TestBSTree, BSTreeEraseEmptyTreeThrow) {
    BSTree<int, int> tree;

    EXPECT_THROW(tree.erase(25), std::logic_error);
}

TEST(TestBSTree, BSTreeEraseTreeWithOneNode) {
    BSTree<int, int> tree;

    tree.insert(1, 1);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), " 1:1\n");

    tree.erase(1);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "");
}
