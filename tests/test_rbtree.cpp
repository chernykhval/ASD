// Copyright 2026 Chernykh Valentin

#include <sstream>
#include <gtest/gtest.h>
#include "libs/lib_rbtree/rbtree.h"

TEST(TestRBTree, IsEmptyOnNewTree) {
    RBTree<int, int> tree;
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(0, tree.size());
}

TEST(TestRBTree, NotEmptyAfterInsert) {
    RBTree<int, int> tree;
    tree.insert(1, 1);
    EXPECT_FALSE(tree.is_empty());
    EXPECT_EQ(1, tree.size());
}

TEST(TestRBTree, InsertDuplicateThrows) {
    RBTree<int, int> tree;
    tree.insert(1, 1);
    EXPECT_THROW(tree.insert(1, 2), std::invalid_argument);
    EXPECT_EQ(1, tree.size());
}

TEST(TestRBTree, FindInEmptyReturnsNullptr) {
    RBTree<int, int> tree;
    EXPECT_EQ(nullptr, tree.find(1));
}

TEST(TestRBTree, FindNonExistentReturnsNullptr) {
    RBTree<int, int> tree;
    tree.insert(5, 50);
    tree.insert(3, 30);
    tree.insert(7, 70);
    EXPECT_EQ(nullptr, tree.find(4));
}

TEST(TestRBTree, FindNonExistentWouldBeChildOfRoot) {
    RBTree<int, int> tree;
    tree.insert(5, 50);
    EXPECT_EQ(nullptr, tree.find(3));
    EXPECT_EQ(nullptr, tree.find(7));
}

TEST(TestRBTree, FindRootReturnsValue) {
    RBTree<int, int> tree;
    tree.insert(5, 50);
    EXPECT_EQ(50, *tree.find(5));
}

TEST(TestRBTree, FindLeafReturnsValue) {
    RBTree<int, int> tree;
    tree.insert(5, 50);
    tree.insert(3, 30);
    tree.insert(7, 70);
    EXPECT_EQ(30, *tree.find(3));
    EXPECT_EQ(70, *tree.find(7));
}

TEST(TestRBTree, FindAllowsModify) {
    RBTree<int, int> tree;
    tree.insert(5, 50);
    *tree.find(5) = 99;
    EXPECT_EQ(99, *tree.find(5));
}

TEST(TestRBTree, ClearEmptiesTree) {
    RBTree<int, int> tree;
    tree.insert(1, 1);
    tree.insert(2, 2);
    tree.insert(3, 3);
    tree.clear();
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(0, tree.size());
    EXPECT_EQ(nullptr, tree.find(1));
}

TEST(TestRBTree, ClearThenInsertWorks) {
    RBTree<int, int> tree;
    tree.insert(1, 1);
    tree.clear();
    tree.insert(2, 2);
    EXPECT_EQ(1, tree.size());
    EXPECT_EQ(2, *tree.find(2));
}

TEST(TestRBTree, SizeAfterInserts) {
    RBTree<int, int> tree;
    tree.insert(1, 1);
    tree.insert(2, 2);
    tree.insert(3, 3);
    EXPECT_EQ(3, tree.size());
}

TEST(TestRBTree, GetKeysEmpty) {
    RBTree<int, int> tree;
    EXPECT_EQ(0, tree.get_keys().size());
}

// вставка 1,2,3 → RR-поворот → корень=2(B), left=1(R), right=3(R)
TEST(TestRBTree, InsertRRCase) {
    RBTree<int, int> tree;
    tree.insert(1, 1);
    tree.insert(2, 2);
    tree.insert(3, 3);

    EXPECT_EQ(1, *tree.find(1));
    EXPECT_EQ(2, *tree.find(2));
    EXPECT_EQ(3, *tree.find(3));

    TVector<int> keys = tree.get_keys();
    EXPECT_EQ(3, keys.size());
    EXPECT_EQ(1, keys[0]);
    EXPECT_EQ(2, keys[1]);
    EXPECT_EQ(3, keys[2]);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);
    EXPECT_EQ("  3:3(R)\n 2:2(B)\n  1:1(R)\n", ss.str());
}

// вставка 3,2,1 → LL-поворот → корень=2(B), left=1(R), right=3(R)
TEST(TestRBTree, InsertLLCase) {
    RBTree<int, int> tree;
    tree.insert(3, 3);
    tree.insert(2, 2);
    tree.insert(1, 1);

    EXPECT_EQ(1, *tree.find(1));
    EXPECT_EQ(2, *tree.find(2));
    EXPECT_EQ(3, *tree.find(3));

    TVector<int> keys = tree.get_keys();
    EXPECT_EQ(1, keys[0]);
    EXPECT_EQ(2, keys[1]);
    EXPECT_EQ(3, keys[2]);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);
    EXPECT_EQ("  3:3(R)\n 2:2(B)\n  1:1(R)\n", ss.str());
}

// вставка 1,3,2 → RL-поворот → корень=2(B), left=1(R), right=3(R)
TEST(TestRBTree, InsertRLCase) {
    RBTree<int, int> tree;
    tree.insert(1, 1);
    tree.insert(3, 3);
    tree.insert(2, 2);

    EXPECT_EQ(1, *tree.find(1));
    EXPECT_EQ(2, *tree.find(2));
    EXPECT_EQ(3, *tree.find(3));

    TVector<int> keys = tree.get_keys();
    EXPECT_EQ(1, keys[0]);
    EXPECT_EQ(2, keys[1]);
    EXPECT_EQ(3, keys[2]);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);
    EXPECT_EQ("  3:3(R)\n 2:2(B)\n  1:1(R)\n", ss.str());
}

// вставка 3,1,2 → LR-поворот → корень=2(B), left=1(R), right=3(R)
TEST(TestRBTree, InsertLRCase) {
    RBTree<int, int> tree;
    tree.insert(3, 3);
    tree.insert(1, 1);
    tree.insert(2, 2);

    EXPECT_EQ(1, *tree.find(1));
    EXPECT_EQ(2, *tree.find(2));
    EXPECT_EQ(3, *tree.find(3));

    TVector<int> keys = tree.get_keys();
    EXPECT_EQ(1, keys[0]);
    EXPECT_EQ(2, keys[1]);
    EXPECT_EQ(3, keys[2]);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);
    EXPECT_EQ("  3:3(R)\n 2:2(B)\n  1:1(R)\n", ss.str());
}

// вставка 4,2,6,1 → дядя=6(R), Case 1: перекраска 2,6 в BLACK
// после: 4(B), 2(B)[1(R)], 6(B)
TEST(TestRBTree, InsertCase1UncleRed) {
    RBTree<int, int> tree;
    tree.insert(4, 4);
    tree.insert(2, 2);
    tree.insert(6, 6);
    tree.insert(1, 1);

    EXPECT_EQ(4, *tree.find(4));
    EXPECT_EQ(2, *tree.find(2));
    EXPECT_EQ(6, *tree.find(6));
    EXPECT_EQ(1, *tree.find(1));
    EXPECT_EQ(4, tree.size());

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);
    // 4(B), right=6(B), left=2(B)[left=1(R)]
    EXPECT_EQ("  6:6(B)\n 4:4(B)\n  2:2(B)\n   1:1(R)\n", ss.str());
}

// полное дерево из 7 узлов с перекрасками
// вставка 4,2,6,1,3,5,7 → 4(B), 2(B)[1(R),3(R)], 6(B)[5(R),7(R)]
TEST(TestRBTree, InsertCase1Propagation) {
    RBTree<int, int> tree;
    int keys[] = {4, 2, 6, 1, 3, 5, 7};
    for (int k : keys) {
        tree.insert(k, k);
    }

    EXPECT_EQ(7, tree.size());
    for (int k : keys) {
        EXPECT_EQ(k, *tree.find(k));
    }

    TVector<int> sorted_keys = tree.get_keys();
    EXPECT_EQ(1, sorted_keys[0]);
    EXPECT_EQ(2, sorted_keys[1]);
    EXPECT_EQ(3, sorted_keys[2]);
    EXPECT_EQ(4, sorted_keys[3]);
    EXPECT_EQ(5, sorted_keys[4]);
    EXPECT_EQ(6, sorted_keys[5]);
    EXPECT_EQ(7, sorted_keys[6]);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);
    // 4(B), right=6(B)[7(R),5(R)], left=2(B)[3(R),1(R)]
    EXPECT_EQ("   7:7(R)\n  6:6(B)\n   5:5(R)\n 4:4(B)\n   3:3(R)\n  2:2(B)\n   1:1(R)\n", ss.str());
}

TEST(TestRBTree, PrintDLCR) {
    RBTree<int, int> tree;
    tree.insert(2, 2);
    tree.insert(1, 1);
    tree.insert(3, 3);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_dlcr();
    std::cout.rdbuf(old);

    EXPECT_EQ("1:1(R), 2:2(B), 3:3(R)\n", ss.str());
}

TEST(TestRBTree, PrintDLRC) {
    RBTree<int, int> tree;
    tree.insert(2, 2);
    tree.insert(1, 1);
    tree.insert(3, 3);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_dlrc();
    std::cout.rdbuf(old);

    EXPECT_EQ("1:1(R), 3:3(R), 2:2(B)\n", ss.str());
}

TEST(TestRBTree, PrintDCLR) {
    RBTree<int, int> tree;
    tree.insert(2, 2);
    tree.insert(1, 1);
    tree.insert(3, 3);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_dclr();
    std::cout.rdbuf(old);

    EXPECT_EQ("2:2(B), 1:1(R), 3:3(R)\n", ss.str());
}

TEST(TestRBTree, PrintW) {
    RBTree<int, int> tree;
    tree.insert(2, 2);
    tree.insert(1, 1);
    tree.insert(3, 3);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_w();
    std::cout.rdbuf(old);

    EXPECT_EQ("2:2(B), 1:1(R), 3:3(R)\n", ss.str());
}

TEST(TestRBTree, PrintTree) {
    RBTree<int, int> tree;
    tree.insert(1, 1);
    tree.insert(2, 2);
    tree.insert(3, 3);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    // после RR: корень=2, right=3, left=1
    EXPECT_EQ("  3:3(R)\n 2:2(B)\n  1:1(R)\n", ss.str());
}

// ──────────────────────────────────────────────
// Erase: базовые случаи
// ──────────────────────────────────────────────

TEST(TestRBTree, EraseFromEmptyThrows) {
    RBTree<int, int> tree;
    EXPECT_THROW(tree.erase(1), std::logic_error);
}

TEST(TestRBTree, EraseNonExistentThrows) {
    RBTree<int, int> tree;
    tree.insert(1, 1);
    EXPECT_THROW(tree.erase(2), std::invalid_argument);
}

TEST(TestRBTree, EraseSingleElement) {
    RBTree<int, int> tree;
    tree.insert(5, 5);
    tree.erase(5);
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(0, tree.size());
    EXPECT_EQ(nullptr, tree.find(5));

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);
    EXPECT_EQ("", ss.str());
}

TEST(TestRBTree, EraseSizeDecrement) {
    RBTree<int, int> tree;
    tree.insert(1, 1);
    tree.insert(2, 2);
    tree.insert(3, 3);
    // после RR: корень=2(B), left=1(R), right=3(R)
    EXPECT_EQ(3, tree.size());

    tree.erase(2);  // 2 потомка, predecessor=1(R) → корень=1(B), right=3(R)
    EXPECT_EQ(2, tree.size());
    {
        std::stringstream ss;
        std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
        tree.print_tree();
        std::cout.rdbuf(old);
        EXPECT_EQ("  3:3(R)\n 1:1(B)\n", ss.str());
    }

    tree.erase(1);  // BLACK с RED потомком 3 → корень=3(B)
    EXPECT_EQ(1, tree.size());
    {
        std::stringstream ss;
        std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
        tree.print_tree();
        std::cout.rdbuf(old);
        EXPECT_EQ(" 3:3(B)\n", ss.str());
    }

    tree.erase(3);
    EXPECT_EQ(0, tree.size());
    {
        std::stringstream ss;
        std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
        tree.print_tree();
        std::cout.rdbuf(old);
        EXPECT_EQ("", ss.str());
    }
}

TEST(TestRBTree, EraseAndReinsert) {
    RBTree<int, int> tree;
    tree.insert(1, 1);
    tree.erase(1);
    tree.insert(1, 99);
    EXPECT_EQ(1, tree.size());
    EXPECT_EQ(99, *tree.find(1));

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);
    EXPECT_EQ(" 1:99(B)\n", ss.str());
}

// ──────────────────────────────────────────────
// Erase: случай 1 — удаление RED листа
// Дерево: 2(B), 1(R), 3(R) — просто удаляем
// ──────────────────────────────────────────────

TEST(TestRBTree, EraseRedLeaf) {
    RBTree<int, int> tree;
    tree.insert(2, 2);
    tree.insert(1, 1);
    tree.insert(3, 3);
    tree.erase(1);
    EXPECT_EQ(2, tree.size());
    EXPECT_EQ(nullptr, tree.find(1));
    EXPECT_EQ(2, *tree.find(2));
    EXPECT_EQ(3, *tree.find(3));

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);
    // 2(B), right=3(R)
    EXPECT_EQ("  3:3(R)\n 2:2(B)\n", ss.str());
}

// ──────────────────────────────────────────────
// Erase: случай 2 — BLACK узел с одним RED потомком
// Дерево: 2(B), 1(R) — перецепляем, красим в BLACK
// ──────────────────────────────────────────────

TEST(TestRBTree, EraseBlackWithRedChild) {
    RBTree<int, int> tree;
    tree.insert(2, 2);
    tree.insert(1, 1);
    // 2(B), 1(R)
    tree.erase(2);
    EXPECT_EQ(1, tree.size());
    EXPECT_EQ(nullptr, tree.find(2));
    EXPECT_EQ(1, *tree.find(1));

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);
    // 1(B) — единственный корень
    EXPECT_EQ(" 1:1(B)\n", ss.str());
}

// ──────────────────────────────────────────────
// Erase: 2 потомка — предшественник RED лист
// Дерево: 2(B), 1(R), 3(R) — удаляем корень
// Предшественник = 1(R), replace_parent == to_erase
// ──────────────────────────────────────────────

TEST(TestRBTree, Erase2ChildrenRedPredecessor) {
    RBTree<int, int> tree;
    tree.insert(2, 2);
    tree.insert(1, 1);
    tree.insert(3, 3);
    // 2(B), 1(R), 3(R)
    tree.erase(2);
    EXPECT_EQ(2, tree.size());
    EXPECT_EQ(nullptr, tree.find(2));
    EXPECT_EQ(1, *tree.find(1));
    EXPECT_EQ(3, *tree.find(3));
    TVector<int> keys = tree.get_keys();
    EXPECT_EQ(1, keys[0]);
    EXPECT_EQ(3, keys[1]);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);
    // корень=1(B), right=3(R)
    EXPECT_EQ("  3:3(R)\n 1:1(B)\n", ss.str());
}

// ──────────────────────────────────────────────
// Erase: 2 потомка — предшественник BLACK с RED ребёнком
// Дерево: 3(B), 2(B), 4(B), 1(R)
// Удаляем 3: предшественник = 2(B), у него левый 1(R) → перецепляем 1, красим BLACK
// replace_parent == to_erase
// ──────────────────────────────────────────────

TEST(TestRBTree, Erase2ChildrenBlackPredecessorWithRedChild) {
    RBTree<int, int> tree;
    tree.insert(3, 3);
    tree.insert(2, 2);
    tree.insert(4, 4);
    tree.insert(1, 1);
    // 3(B), 2(B), 4(B), 1(R)
    tree.erase(3);
    EXPECT_EQ(3, tree.size());
    EXPECT_EQ(nullptr, tree.find(3));
    EXPECT_EQ(1, *tree.find(1));
    EXPECT_EQ(2, *tree.find(2));
    EXPECT_EQ(4, *tree.find(4));
    TVector<int> keys = tree.get_keys();
    EXPECT_EQ(1, keys[0]);
    EXPECT_EQ(2, keys[1]);
    EXPECT_EQ(4, keys[2]);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);
    // корень=2(B), left=1(B), right=4(B)
    EXPECT_EQ("  4:4(B)\n 2:2(B)\n  1:1(B)\n", ss.str());
}

// ──────────────────────────────────────────────
// Erase: 2 потомка — предшественник BLACK лист, глубже
// Дерево: 4(B), 2(R), 6(R), 1(B), 3(B), 5(B), 7(B)
// Удаляем 4: предшественник = 3(B), replace_parent=2(R) ≠ to_erase
// fix: Case B (p=RED) → 1→RED, 2→BLACK
// ──────────────────────────────────────────────

TEST(TestRBTree, Erase2ChildrenBlackPredecessorDeep) {
    RBTree<int, int> tree;
    for (int k : {4, 2, 6, 1, 3, 5, 7}) tree.insert(k, k);
    // 4(B), 2(B), 6(B), 1(R), 3(R), 5(R), 7(R)
    // predecessor = 3(R) → no fix, just copy+delete
    tree.erase(4);
    EXPECT_EQ(6, tree.size());
    EXPECT_EQ(nullptr, tree.find(4));
    for (int k : {1, 2, 3, 5, 6, 7}) EXPECT_EQ(k, *tree.find(k));
    TVector<int> keys = tree.get_keys();
    EXPECT_EQ(1, keys[0]);
    EXPECT_EQ(2, keys[1]);
    EXPECT_EQ(3, keys[2]);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);
    // корень=3(B), left=2(B)[left=1(R)], right=6(B)[left=5(R),right=7(R)]
    EXPECT_EQ("   7:7(R)\n  6:6(B)\n   5:5(R)\n 3:3(B)\n  2:2(B)\n   1:1(R)\n", ss.str());
}

// ──────────────────────────────────────────────
// fix_double_black Case B — родитель RED
// Дерево: 4(B), 2(R), 6(R), 1(B), 3(B), 5(B), 7(B)
// Удаляем 7: [DB] у 6->right, s=5(B) без детей, p=6(R)
// → 5→RED, 6→BLACK, готово
// ──────────────────────────────────────────────

TEST(TestRBTree, EraseFixCaseBRedParent) {
    RBTree<int, int> tree;
    for (int k : {4, 2, 6, 1, 3, 5, 7}) tree.insert(k, k);
    // 4(B), 2(B), 6(B), 1(R), 3(R), 5(R), 7(R) — 7 is RED leaf
    tree.erase(7);
    EXPECT_EQ(6, tree.size());
    EXPECT_EQ(nullptr, tree.find(7));
    TVector<int> keys = tree.get_keys();
    EXPECT_EQ(1, keys[0]);
    EXPECT_EQ(2, keys[1]);
    EXPECT_EQ(3, keys[2]);
    EXPECT_EQ(4, keys[3]);
    EXPECT_EQ(5, keys[4]);
    EXPECT_EQ(6, keys[5]);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);
    // 4(B), 2(B)[1(R),3(R)], 6(B)[5(R)]
    EXPECT_EQ("  6:6(B)\n   5:5(R)\n 4:4(B)\n   3:3(R)\n  2:2(B)\n   1:1(R)\n", ss.str());
}

// ──────────────────────────────────────────────
// fix_double_black Case B — родитель BLACK, подъём до корня
// Цепочка удалений доводит [DB] до корня
// ──────────────────────────────────────────────

TEST(TestRBTree, EraseFixCaseBBlackParentPropagateToRoot) {
    RBTree<int, int> tree;
    for (int k : {4, 2, 6, 1, 3, 5, 7}) tree.insert(k, k);
    // все листы RED → erase(1,3,5,7) просто удаляет RED листы
    tree.erase(1);
    tree.erase(3);
    tree.erase(5);
    tree.erase(7);
    // теперь: 4(B), 2(B), 6(B) — все без потомков
    tree.erase(2);  // Case B p=4(B): 6→RED, [DB] поднимается до корня
    EXPECT_EQ(2, tree.size());
    EXPECT_EQ(nullptr, tree.find(2));
    EXPECT_EQ(4, *tree.find(4));
    EXPECT_EQ(6, *tree.find(6));
    TVector<int> keys = tree.get_keys();
    EXPECT_EQ(4, keys[0]);
    EXPECT_EQ(6, keys[1]);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);
    // корень=4(B), right=6(R)
    EXPECT_EQ("  6:6(R)\n 4:4(B)\n", ss.str());
}

// ──────────────────────────────────────────────
// fix_double_black Case C — дальний ребёнок s RED (ближний BLACK)
// Дерево: 4(B), 2(B), 6(B), 1(R)
// Удаляем 6: [DB] у 4->right, s=2(B), near=NULL(B), far=1(R)
// → right_rotate(4), swap_color(4,2), 1→BLACK
// ──────────────────────────────────────────────

TEST(TestRBTree, EraseFixCaseC) {
    RBTree<int, int> tree;
    tree.insert(4, 4);
    tree.insert(2, 2);
    tree.insert(6, 6);
    tree.insert(1, 1);
    // 4(B), 2(B), 6(B), 1(R)
    tree.erase(6);
    EXPECT_EQ(3, tree.size());
    EXPECT_EQ(nullptr, tree.find(6));
    EXPECT_EQ(1, *tree.find(1));
    EXPECT_EQ(2, *tree.find(2));
    EXPECT_EQ(4, *tree.find(4));
    TVector<int> keys = tree.get_keys();
    EXPECT_EQ(1, keys[0]);
    EXPECT_EQ(2, keys[1]);
    EXPECT_EQ(4, keys[2]);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);
    // корень=2(B), left=1(B), right=4(B)
    EXPECT_EQ("  4:4(B)\n 2:2(B)\n  1:1(B)\n", ss.str());
}

// ──────────────────────────────────────────────
// fix_double_black Case D → Case C
// Дерево: 4(B), 2(B), 6(B), 5(R)
// Удаляем 2: [DB] у 4->left, s=6(B), near=5(R), far=NULL(B)
// → right_rotate(6) + swap → left_rotate(4) + swap + 6→BLACK
// ──────────────────────────────────────────────

TEST(TestRBTree, EraseFixCaseD) {
    RBTree<int, int> tree;
    tree.insert(4, 4);
    tree.insert(2, 2);
    tree.insert(6, 6);
    tree.insert(5, 5);
    // 4(B), 2(B), 6(B), 5(R)
    tree.erase(2);
    EXPECT_EQ(3, tree.size());
    EXPECT_EQ(nullptr, tree.find(2));
    EXPECT_EQ(4, *tree.find(4));
    EXPECT_EQ(5, *tree.find(5));
    EXPECT_EQ(6, *tree.find(6));
    TVector<int> keys = tree.get_keys();
    EXPECT_EQ(4, keys[0]);
    EXPECT_EQ(5, keys[1]);
    EXPECT_EQ(6, keys[2]);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);
    // корень=5(B), left=4(B), right=6(B)
    EXPECT_EQ("  6:6(B)\n 5:5(B)\n  4:4(B)\n", ss.str());
}

// ──────────────────────────────────────────────
// fix_double_black Case D→C (повторный)
// Дерево: 4(B),2(B),6(B),1(R),3(R),5(R),7(R)
// После erase 1,3 (RED листы): 4(B),2(B),6(B),5(R),7(R), 2 без детей
// Удаляем 2: [DB] у 4->left, s=6(B), near=5(R) → Case D→C
// ──────────────────────────────────────────────

TEST(TestRBTree, EraseFixCaseDC) {
    RBTree<int, int> tree;
    for (int k : {4, 2, 6, 1, 3, 5, 7}) tree.insert(k, k);
    tree.erase(1);
    tree.erase(3);
    tree.erase(2);
    EXPECT_EQ(4, tree.size());
    EXPECT_EQ(nullptr, tree.find(2));
    EXPECT_EQ(4, *tree.find(4));
    EXPECT_EQ(5, *tree.find(5));
    EXPECT_EQ(6, *tree.find(6));
    EXPECT_EQ(7, *tree.find(7));
    TVector<int> keys = tree.get_keys();
    EXPECT_EQ(4, keys[0]);
    EXPECT_EQ(5, keys[1]);
    EXPECT_EQ(6, keys[2]);
    EXPECT_EQ(7, keys[3]);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);
    // корень=5(B), left=4(B), right=6(B)[right=7(R)]
    EXPECT_EQ("   7:7(R)\n  6:6(B)\n 5:5(B)\n  4:4(B)\n", ss.str());
}

// ──────────────────────────────────────────────
// fix_double_black Case A — брат RED
// Вставка 8 вызывает Case 1 → 6 становится RED
// Дерево: 4(B),2(B),6(R),1(R),3(R),5(B),7(B),8(R)
// После erase 1,3 (RED листы): 4(B),2(B),6(R),5(B),7(B),8(R), 2 без детей
// Удаляем 2: [DB] у 4->left, s=6(R) → Case A → далее Case B p=RED
// ──────────────────────────────────────────────

TEST(TestRBTree, EraseFixCaseA) {
    RBTree<int, int> tree;
    for (int k : {4, 2, 6, 1, 3, 5, 7}) tree.insert(k, k);
    tree.insert(8, 8);  // Case 1 при вставке: 5→B, 7→B, 6→R
    tree.erase(1);      // RED лист
    tree.erase(3);      // RED лист
    // теперь: 4(B), 2(B), 6(R), 5(B), 7(B), 8(R)
    tree.erase(2);  // [DB] у 4->left, s=6(R) → Case A → далее Case B p=RED
    EXPECT_EQ(5, tree.size());
    EXPECT_EQ(nullptr, tree.find(2));
    for (int k : {4, 5, 6, 7, 8}) EXPECT_EQ(k, *tree.find(k));
    TVector<int> keys = tree.get_keys();
    EXPECT_EQ(4, keys[0]);
    EXPECT_EQ(5, keys[1]);
    EXPECT_EQ(6, keys[2]);
    EXPECT_EQ(7, keys[3]);
    EXPECT_EQ(8, keys[4]);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);
    // корень=6(B), left=4(B)[right=5(R)], right=7(B)[right=8(R)]
    EXPECT_EQ("   8:8(R)\n  7:7(B)\n 6:6(B)\n   5:5(R)\n  4:4(B)\n", ss.str());
}

// ──────────────────────────────────────────────
// Удаление всех элементов подряд
// ──────────────────────────────────────────────

TEST(TestRBTree, EraseAllElements) {
    RBTree<int, int> tree;
    for (int k : {4, 2, 6, 1, 3, 5, 7}) tree.insert(k, k);
    for (int k : {4, 2, 6, 1, 3, 5, 7}) tree.erase(k);
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(0, tree.size());

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);
    EXPECT_EQ("", ss.str());
}

// ──────────────────────────────────────────────
// Удаление не-корневого узла с 2 потомками, predecessor — прямой RED потомок
// Дерево: 8(B), 4(B)[2(R),6(R)], 12(B)[10(R),14(R)]
// Удаляем 12: predecessor=10(R) — прямой левый потомок, replace_parent==to_erase
// ──────────────────────────────────────────────

TEST(TestRBTree, EraseNonRootWith2Children) {
    RBTree<int, int> tree;
    for (int k : {8, 4, 12, 2, 6, 10, 14}) tree.insert(k, k);
    tree.erase(12);
    EXPECT_EQ(6, tree.size());
    EXPECT_EQ(nullptr, tree.find(12));
    for (int k : {2, 4, 6, 8, 10, 14}) EXPECT_EQ(k, *tree.find(k));
    TVector<int> keys = tree.get_keys();
    EXPECT_EQ(2,  keys[0]);
    EXPECT_EQ(4,  keys[1]);
    EXPECT_EQ(6,  keys[2]);
    EXPECT_EQ(8,  keys[3]);
    EXPECT_EQ(10, keys[4]);
    EXPECT_EQ(14, keys[5]);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);
    // 8(B), left=4(B)[2(R),6(R)], right=10(B)[14(R)]
    EXPECT_EQ("   14:14(R)\n  10:10(B)\n 8:8(B)\n   6:6(R)\n  4:4(B)\n   2:2(R)\n", ss.str());
}

// ──────────────────────────────────────────────
// Удаление не-корневого узла с 2 потомками, predecessor — глубже (не прямой потомок)
// Дерево: 8(B), 4(R)[2(B)[1(R),3(R)],6(B)], 12(B)[10(R),14(R)]
// Удаляем 4: predecessor=3(R), replace_parent=2 ≠ to_erase
// ──────────────────────────────────────────────

TEST(TestRBTree, EraseNonRootWith2ChildrenPredecessorDeep) {
    RBTree<int, int> tree;
    for (int k : {8, 4, 12, 2, 6, 10, 14, 1, 3}) tree.insert(k, k);
    tree.erase(4);
    EXPECT_EQ(8, tree.size());
    EXPECT_EQ(nullptr, tree.find(4));
    for (int k : {1, 2, 3, 6, 8, 10, 12, 14}) EXPECT_EQ(k, *tree.find(k));
    TVector<int> keys = tree.get_keys();
    EXPECT_EQ(1,  keys[0]);
    EXPECT_EQ(2,  keys[1]);
    EXPECT_EQ(3,  keys[2]);
    EXPECT_EQ(6,  keys[3]);
    EXPECT_EQ(8,  keys[4]);
    EXPECT_EQ(10, keys[5]);
    EXPECT_EQ(12, keys[6]);
    EXPECT_EQ(14, keys[7]);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);
    // 8(B), left=3(R)[2(B)[1(R)],6(B)], right=12(B)[10(R),14(R)]
    EXPECT_EQ("   14:14(R)\n  12:12(B)\n   10:10(R)\n 8:8(B)\n   6:6(B)\n  3:3(R)\n   2:2(B)\n    1:1(R)\n", ss.str());
}

// ──────────────────────────────────────────────
// Стресс-тест: чередование вставок и удалений
// 1) Вставка {4,2,6,1,3,5,7}, удаление всех RED листов {3,5,1,7}
// 2) Вставка {8,0}
// 3) Удаление корня 4 (predecessor=2(B) с RED потомком 0)
// ──────────────────────────────────────────────

TEST(TestRBTree, StressInsertErase) {
    RBTree<int, int> tree;
    for (int k : {4, 2, 6, 1, 3, 5, 7}) tree.insert(k, k);

    tree.erase(3);
    tree.erase(5);
    tree.erase(1);
    tree.erase(7);
    EXPECT_EQ(3, tree.size());
    for (int k : {2, 4, 6}) EXPECT_EQ(k, *tree.find(k));
    for (int k : {1, 3, 5, 7}) EXPECT_EQ(nullptr, tree.find(k));
    // Дерево: 4(B), 2(B), 6(B)

    tree.insert(8, 8);
    tree.insert(0, 0);
    EXPECT_EQ(5, tree.size());
    // Дерево: 4(B)[2(B)[0(R)], 6(B)[8(R)]]

    tree.erase(4);  // корень, 2 потомка; predecessor=2(B)[left=0(R)] → BLACK+RED child
    EXPECT_EQ(4, tree.size());
    EXPECT_EQ(nullptr, tree.find(4));
    for (int k : {0, 2, 6, 8}) EXPECT_EQ(k, *tree.find(k));
    TVector<int> keys = tree.get_keys();
    EXPECT_EQ(0, keys[0]);
    EXPECT_EQ(2, keys[1]);
    EXPECT_EQ(6, keys[2]);
    EXPECT_EQ(8, keys[3]);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);
    // корень=2(B), left=0(B), right=6(B)[right=8(R)]
    EXPECT_EQ("   8:8(R)\n  6:6(B)\n 2:2(B)\n  0:0(B)\n", ss.str());
}

// ──────────────────────────────────────────────
// Erase: predecessor не прямой потомок, имеет левый RED ребёнок
// {10,5,15,3,7,6} → 10(B)[5(R)[3(B),7(B)[6(R)]], 15(B)]
// Удаляем 10: predecessor=7(B), replace_parent=5 ≠ to_erase
// 7 имеет левый ребёнок 6(R) → перецепляем 6 к 5, красим BLACK
// ──────────────────────────────────────────────

TEST(TestRBTree, ErasePredecessorNotDirectChildHasRedLeftChild) {
    RBTree<int, int> tree;
    for (int k : {10, 5, 15, 3, 7, 6}) tree.insert(k, k);
    tree.erase(10);
    EXPECT_EQ(5, tree.size());
    EXPECT_EQ(nullptr, tree.find(10));
    for (int k : {3, 5, 6, 7, 15}) EXPECT_EQ(k, *tree.find(k));
    TVector<int> keys = tree.get_keys();
    EXPECT_EQ(3,  keys[0]);
    EXPECT_EQ(5,  keys[1]);
    EXPECT_EQ(6,  keys[2]);
    EXPECT_EQ(7,  keys[3]);
    EXPECT_EQ(15, keys[4]);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);
    // корень=7(B), left=5(R)[3(B),6(B)], right=15(B)
    EXPECT_EQ("  15:15(B)\n 7:7(B)\n   6:6(B)\n  5:5(R)\n   3:3(B)\n", ss.str());
}
