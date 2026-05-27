// Copyright 2026 Chernykh Valentin

#include <gtest/gtest.h>
#include <string>
#include "libs/lib_table/table.h"
#include "libs/lib_rbtree/rbtree.h"
#include "libs/lib_avltree/avltree.h"
#include "libs/lib_bstree/bstree.h"
#include "libs/lib_btree/btree.h"
#include "libs/lib_unordered_array_table/unordered_array_table.h"
#include "libs/lib_unordered_list_table/unordered_list_table.h"
#include "libs/lib_ordered_array_table/ordered_array_table.h"
#include "libs/lib_unordered_array_storage/unordered_array_storage.h"
#include "libs/lib_unordered_list_storage/unordered_list_storage.h"
#include "libs/lib_ordered_array_storage/ordered_array_storage.h"
#include "libs/lib_tvector/tvector.h"

// ──────────────────────────────────────────────
// RBTree
// ──────────────────────────────────────────────

TEST(TestTableOnRBTree, insert) {
    Table<RBTree<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    EXPECT_EQ(1, table.size());
}

TEST(TestTableOnRBTree, insert_duplicate_throws) {
    Table<RBTree<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    EXPECT_THROW(table.insert(1, "one"), std::invalid_argument);
}

TEST(TestTableOnRBTree, erase) {
    Table<RBTree<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    EXPECT_TRUE(table.erase(1));
    EXPECT_FALSE(table.erase(1));
    EXPECT_EQ(0, table.size());
}

TEST(TestTableOnRBTree, erase_missing) {
    Table<RBTree<int, std::string>, int, std::string> table;
    EXPECT_FALSE(table.erase(42));
}

TEST(TestTableOnRBTree, find) {
    Table<RBTree<int, std::string>, int, std::string> table;
    EXPECT_EQ(nullptr, table.find(1));
    table.insert(1, "one");
    EXPECT_EQ("one", *table.find(1));
}

TEST(TestTableOnRBTree, is_empty_and_clear) {
    Table<RBTree<int, std::string>, int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(1, "one");
    EXPECT_FALSE(table.is_empty());
    table.clear();
    EXPECT_TRUE(table.is_empty());
}

TEST(TestTableOnRBTree, contains) {
    Table<RBTree<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    EXPECT_TRUE(table.contains(1));
    table.erase(1);
    EXPECT_FALSE(table.contains(1));
}

TEST(TestTableOnRBTree, get_keys_sorted) {
    Table<RBTree<int, std::string>, int, std::string> table;
    table.insert(3, "three");
    table.insert(1, "one");
    table.insert(2, "two");
    TVector<int> keys = table.get_keys();
    EXPECT_EQ(3, keys.size());
    EXPECT_EQ(1, keys[0]);
    EXPECT_EQ(2, keys[1]);
    EXPECT_EQ(3, keys[2]);
}

TEST(TestTableOnRBTree, to_string) {
    Table<RBTree<int, std::string>, int, std::string> table;
    table.insert(2, "two");
    table.insert(1, "one");
    table.insert(3, "three");
    std::string expected = "{key} : {value}\n"
                           "{1} : {one}\n"
                           "{2} : {two}\n"
                           "{3} : {three}\n";
    EXPECT_EQ(expected, table.to_string());
}

TEST(TestTableOnRBTree, to_string_empty) {
    Table<RBTree<int, std::string>, int, std::string> table;
    EXPECT_EQ("Table is empty\n", table.to_string());
}

// ──────────────────────────────────────────────
// AVLTree
// ──────────────────────────────────────────────

TEST(TestTableOnAVLTree, insert) {
    Table<AVLTree<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    EXPECT_EQ(1, table.size());
}

TEST(TestTableOnAVLTree, erase) {
    Table<AVLTree<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    EXPECT_TRUE(table.erase(1));
    EXPECT_FALSE(table.erase(1));
}

TEST(TestTableOnAVLTree, find) {
    Table<AVLTree<int, std::string>, int, std::string> table;
    EXPECT_EQ(nullptr, table.find(1));
    table.insert(1, "one");
    EXPECT_EQ("one", *table.find(1));
}

TEST(TestTableOnAVLTree, get_keys_sorted) {
    Table<AVLTree<int, std::string>, int, std::string> table;
    table.insert(3, "three");
    table.insert(1, "one");
    table.insert(2, "two");
    TVector<int> keys = table.get_keys();
    EXPECT_EQ(3, keys.size());
    EXPECT_EQ(1, keys[0]);
    EXPECT_EQ(2, keys[1]);
    EXPECT_EQ(3, keys[2]);
}

TEST(TestTableOnAVLTree, to_string) {
    Table<AVLTree<int, std::string>, int, std::string> table;
    table.insert(2, "two");
    table.insert(1, "one");
    table.insert(3, "three");
    std::string expected = "{key} : {value}\n"
                           "{1} : {one}\n"
                           "{2} : {two}\n"
                           "{3} : {three}\n";
    EXPECT_EQ(expected, table.to_string());
}

// ──────────────────────────────────────────────
// BSTree
// ──────────────────────────────────────────────

TEST(TestTableOnBSTree, insert) {
    Table<BSTree<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    EXPECT_EQ(1, table.size());
}

TEST(TestTableOnBSTree, erase) {
    Table<BSTree<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    EXPECT_TRUE(table.erase(1));
    EXPECT_FALSE(table.erase(1));
}

TEST(TestTableOnBSTree, find) {
    Table<BSTree<int, std::string>, int, std::string> table;
    EXPECT_EQ(nullptr, table.find(1));
    table.insert(1, "one");
    EXPECT_EQ("one", *table.find(1));
}

TEST(TestTableOnBSTree, get_keys_sorted) {
    Table<BSTree<int, std::string>, int, std::string> table;
    table.insert(3, "three");
    table.insert(1, "one");
    table.insert(2, "two");
    TVector<int> keys = table.get_keys();
    EXPECT_EQ(3, keys.size());
    EXPECT_EQ(1, keys[0]);
    EXPECT_EQ(2, keys[1]);
    EXPECT_EQ(3, keys[2]);
}

TEST(TestTableOnBSTree, to_string) {
    Table<BSTree<int, std::string>, int, std::string> table;
    table.insert(2, "two");
    table.insert(1, "one");
    table.insert(3, "three");
    std::string expected = "{key} : {value}\n"
                           "{1} : {one}\n"
                           "{2} : {two}\n"
                           "{3} : {three}\n";
    EXPECT_EQ(expected, table.to_string());
}

// ──────────────────────────────────────────────
// BTree
// ──────────────────────────────────────────────

TEST(TestTableOnBTree, insert) {
    Table<BTree<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    EXPECT_EQ(1, table.size());
}

TEST(TestTableOnBTree, erase) {
    Table<BTree<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    EXPECT_TRUE(table.erase(1));
    EXPECT_FALSE(table.erase(1));
    EXPECT_EQ(0, table.size());
}

TEST(TestTableOnBTree, find) {
    Table<BTree<int, std::string>, int, std::string> table;
    EXPECT_EQ(nullptr, table.find(1));
    table.insert(1, "one");
    EXPECT_EQ("one", *table.find(1));
}

TEST(TestTableOnBTree, get_keys) {
    Table<BTree<int, std::string>, int, std::string> table;
    table.insert(3, "three");
    table.insert(1, "one");
    table.insert(2, "two");
    TVector<int> keys = table.get_keys();
    EXPECT_EQ(3, keys.size());
}

// ──────────────────────────────────────────────
// UnorderedArrayTable as Storage
// ──────────────────────────────────────────────

TEST(TestTableOnUnorderedArrayTable, insert_and_find) {
    Table<UnorderedArrayTable<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    EXPECT_EQ(1, table.size());
    EXPECT_EQ("one", *table.find(1));
}

TEST(TestTableOnUnorderedArrayTable, erase) {
    Table<UnorderedArrayTable<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    EXPECT_TRUE(table.erase(1));
    EXPECT_FALSE(table.erase(1));
}

TEST(TestTableOnUnorderedArrayTable, contains_and_clear) {
    Table<UnorderedArrayTable<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    EXPECT_TRUE(table.contains(1));
    EXPECT_FALSE(table.contains(99));
    table.clear();
    EXPECT_TRUE(table.is_empty());
}

TEST(TestTableOnUnorderedArrayTable, insert_duplicate_throws) {
    Table<UnorderedArrayTable<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    EXPECT_THROW(table.insert(1, "one"), std::invalid_argument);
}

TEST(TestTableOnUnorderedArrayTable, find_nullptr) {
    Table<UnorderedArrayTable<int, std::string>, int, std::string> table;
    EXPECT_EQ(nullptr, table.find(99));
}

TEST(TestTableOnUnorderedArrayTable, to_string_contains_entries) {
    Table<UnorderedArrayTable<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    std::string result = table.to_string();
    EXPECT_NE(std::string::npos, result.find("{1} : {one}"));
    EXPECT_NE(std::string::npos, result.find("{2} : {two}"));
}

// ──────────────────────────────────────────────
// UnorderedListTable as Storage
// ──────────────────────────────────────────────

TEST(TestTableOnUnorderedListTable, insert_and_find) {
    Table<UnorderedListTable<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    EXPECT_EQ(1, table.size());
    EXPECT_EQ("one", *table.find(1));
}

TEST(TestTableOnUnorderedListTable, erase) {
    Table<UnorderedListTable<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    EXPECT_TRUE(table.erase(1));
    EXPECT_FALSE(table.erase(1));
}

TEST(TestTableOnUnorderedListTable, insert_duplicate_throws) {
    Table<UnorderedListTable<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    EXPECT_THROW(table.insert(1, "one"), std::invalid_argument);
}

TEST(TestTableOnUnorderedListTable, find_nullptr) {
    Table<UnorderedListTable<int, std::string>, int, std::string> table;
    EXPECT_EQ(nullptr, table.find(99));
}

TEST(TestTableOnUnorderedListTable, is_empty_and_clear) {
    Table<UnorderedListTable<int, std::string>, int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(1, "one");
    EXPECT_FALSE(table.is_empty());
    table.clear();
    EXPECT_TRUE(table.is_empty());
}

TEST(TestTableOnUnorderedListTable, to_string_contains_entries) {
    Table<UnorderedListTable<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    std::string result = table.to_string();
    EXPECT_NE(std::string::npos, result.find("{1} : {one}"));
    EXPECT_NE(std::string::npos, result.find("{2} : {two}"));
}

// ──────────────────────────────────────────────
// OrderedArrayTable as Storage
// ──────────────────────────────────────────────

TEST(TestTableOnOrderedArrayTable, insert_and_find) {
    Table<OrderedArrayTable<int, std::string>, int, std::string> table;
    table.insert(3, "three");
    table.insert(1, "one");
    table.insert(2, "two");
    EXPECT_EQ(3, table.size());
    EXPECT_EQ("one", *table.find(1));
}

TEST(TestTableOnOrderedArrayTable, erase) {
    Table<OrderedArrayTable<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    EXPECT_TRUE(table.erase(1));
    EXPECT_FALSE(table.erase(1));
}

TEST(TestTableOnOrderedArrayTable, insert_duplicate_throws) {
    Table<OrderedArrayTable<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    EXPECT_THROW(table.insert(1, "one"), std::invalid_argument);
}

TEST(TestTableOnOrderedArrayTable, find_nullptr) {
    Table<OrderedArrayTable<int, std::string>, int, std::string> table;
    EXPECT_EQ(nullptr, table.find(99));
}

TEST(TestTableOnOrderedArrayTable, is_empty_and_clear) {
    Table<OrderedArrayTable<int, std::string>, int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(1, "one");
    EXPECT_FALSE(table.is_empty());
    table.clear();
    EXPECT_TRUE(table.is_empty());
}

TEST(TestTableOnOrderedArrayTable, to_string_sorted) {
    Table<OrderedArrayTable<int, std::string>, int, std::string> table;
    table.insert(3, "three");
    table.insert(1, "one");
    table.insert(2, "two");
    std::string expected = "{key} : {value}\n"
                           "{1} : {one}\n"
                           "{2} : {two}\n"
                           "{3} : {three}\n";
    EXPECT_EQ(expected, table.to_string());
}

// ──────────────────────────────────────────────
// UnorderedArrayStorage
// ──────────────────────────────────────────────

TEST(TestTableOnUnorderedArrayStorage, insert_and_find) {
    Table<UnorderedArrayStorage<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    EXPECT_EQ(1, table.size());
    EXPECT_EQ("one", *table.find(1));
}

TEST(TestTableOnUnorderedArrayStorage, erase) {
    Table<UnorderedArrayStorage<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    EXPECT_TRUE(table.erase(1));
    EXPECT_FALSE(table.erase(1));
}

TEST(TestTableOnUnorderedArrayStorage, insert_duplicate_throws) {
    Table<UnorderedArrayStorage<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    EXPECT_THROW(table.insert(1, "one"), std::invalid_argument);
}

TEST(TestTableOnUnorderedArrayStorage, find_nullptr) {
    Table<UnorderedArrayStorage<int, std::string>, int, std::string> table;
    EXPECT_EQ(nullptr, table.find(99));
}

TEST(TestTableOnUnorderedArrayStorage, is_empty_and_clear) {
    Table<UnorderedArrayStorage<int, std::string>, int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(1, "one");
    EXPECT_FALSE(table.is_empty());
    table.clear();
    EXPECT_TRUE(table.is_empty());
}

TEST(TestTableOnUnorderedArrayStorage, to_string_contains_entries) {
    Table<UnorderedArrayStorage<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    std::string result = table.to_string();
    EXPECT_NE(std::string::npos, result.find("{1} : {one}"));
    EXPECT_NE(std::string::npos, result.find("{2} : {two}"));
}

// ──────────────────────────────────────────────
// UnorderedListStorage
// ──────────────────────────────────────────────

TEST(TestTableOnUnorderedListStorage, insert_and_find) {
    Table<UnorderedListStorage<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    EXPECT_EQ(1, table.size());
    EXPECT_EQ("one", *table.find(1));
}

TEST(TestTableOnUnorderedListStorage, erase) {
    Table<UnorderedListStorage<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    EXPECT_TRUE(table.erase(1));
    EXPECT_FALSE(table.erase(1));
}

TEST(TestTableOnUnorderedListStorage, insert_duplicate_throws) {
    Table<UnorderedListStorage<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    EXPECT_THROW(table.insert(1, "one"), std::invalid_argument);
}

TEST(TestTableOnUnorderedListStorage, find_nullptr) {
    Table<UnorderedListStorage<int, std::string>, int, std::string> table;
    EXPECT_EQ(nullptr, table.find(99));
}

TEST(TestTableOnUnorderedListStorage, is_empty_and_clear) {
    Table<UnorderedListStorage<int, std::string>, int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(1, "one");
    EXPECT_FALSE(table.is_empty());
    table.clear();
    EXPECT_TRUE(table.is_empty());
}

// ──────────────────────────────────────────────
// OrderedArrayStorage
// ──────────────────────────────────────────────

TEST(TestTableOnOrderedArrayStorage, insert_and_find) {
    Table<OrderedArrayStorage<int, std::string>, int, std::string> table;
    table.insert(3, "three");
    table.insert(1, "one");
    table.insert(2, "two");
    EXPECT_EQ(3, table.size());
    EXPECT_EQ("one", *table.find(1));
}

TEST(TestTableOnOrderedArrayStorage, erase) {
    Table<OrderedArrayStorage<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    EXPECT_TRUE(table.erase(1));
    EXPECT_FALSE(table.erase(1));
}

TEST(TestTableOnOrderedArrayStorage, insert_duplicate_throws) {
    Table<OrderedArrayStorage<int, std::string>, int, std::string> table;
    table.insert(1, "one");
    EXPECT_THROW(table.insert(1, "one"), std::invalid_argument);
}

TEST(TestTableOnOrderedArrayStorage, find_nullptr) {
    Table<OrderedArrayStorage<int, std::string>, int, std::string> table;
    EXPECT_EQ(nullptr, table.find(99));
}

TEST(TestTableOnOrderedArrayStorage, is_empty_and_clear) {
    Table<OrderedArrayStorage<int, std::string>, int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(1, "one");
    EXPECT_FALSE(table.is_empty());
    table.clear();
    EXPECT_TRUE(table.is_empty());
}

TEST(TestTableOnOrderedArrayStorage, to_string_sorted) {
    Table<OrderedArrayStorage<int, std::string>, int, std::string> table;
    table.insert(3, "three");
    table.insert(1, "one");
    table.insert(2, "two");
    std::string expected = "{key} : {value}\n"
                           "{1} : {one}\n"
                           "{2} : {two}\n"
                           "{3} : {three}\n";
    EXPECT_EQ(expected, table.to_string());
}
