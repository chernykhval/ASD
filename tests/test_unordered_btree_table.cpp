// Copyright 2026 Chernykh Valentin

#include <gtest/gtest.h>
#include <string>
#include "libs/lib_unordered_btree_table/unordered_btree_table.h"
#include "libs/lib_tvector/tvector.h"

#define EPSILON 0.000001

TEST(TestUnorderedBTreeTable, insert) {
    UnorderedBTreeTable<int, std::string> table;

    table.insert(1, "hello");

    EXPECT_EQ(1, table.size());
}

TEST(TestUnorderedBTreeTable, insert_exception) {
    UnorderedBTreeTable<int, std::string> table;

    table.insert(1, "hello");

    EXPECT_THROW(table.insert(1, "hello"), std::invalid_argument);
}

TEST(TestUnorderedBTreeTable, erase_true) {
    UnorderedBTreeTable<int, std::string> table;

    table.insert(1, "hello");

    EXPECT_TRUE(table.erase(1));
    EXPECT_FALSE(table.erase(1));
    EXPECT_EQ(0, table.size());
}

TEST(TestUnorderedBTreeTable, erase_false) {
    UnorderedBTreeTable<int, std::string> table;

    table.insert(1, "hello");

    EXPECT_FALSE(table.erase(2));
}

TEST(TestUnorderedBTreeTable, find) {
    UnorderedBTreeTable<int, std::string> table;

    EXPECT_EQ(nullptr, table.find(1));
    table.insert(1, "hello");
    EXPECT_EQ("hello", *table.find(1));
}

TEST(TestUnorderedBTreeTable, is_empty_and_clear) {
    UnorderedBTreeTable<int, std::string> table;

    EXPECT_EQ(true, table.is_empty());
    table.insert(1, "hello");
    EXPECT_EQ(false, table.is_empty());
    table.clear();
    EXPECT_EQ(true, table.is_empty());
}

TEST(TestUnorderedBTreeTable, multiple_elements_scenario) {
    UnorderedBTreeTable<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    EXPECT_EQ(3, table.size());

    EXPECT_EQ("one", *table.find(1));
    EXPECT_EQ("two", *table.find(2));
    EXPECT_EQ("three", *table.find(3));

    table.erase(2);

    EXPECT_EQ(2, table.size());
    EXPECT_EQ(nullptr, table.find(2));
    EXPECT_EQ("one", *table.find(1));
    EXPECT_EQ("three", *table.find(3));
}

TEST(TestUnorderedBTreeTable, to_string) {
    UnorderedBTreeTable<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    std::string text = "{key} : {value}\n"
                       "{1} : {one}\n"
                       "{2} : {two}\n"
                       "{3} : {three}\n";

    EXPECT_EQ(text, table.to_string());
}

TEST(TestUnorderedBTreeTable, ToStringForEmptyTable) {
    UnorderedBTreeTable<int, std::string> table;

    std::string text = "Table is empty\n";

    EXPECT_EQ(text, table.to_string());
}

TEST(TestUnorderedBTreeTable, contains) {
    UnorderedBTreeTable<int, std::string> table;

    table.insert(1, "one");

    EXPECT_TRUE(table.contains(1));

    table.erase(1);

    EXPECT_FALSE(table.contains(1));
}

TEST(TestUnorderedBTreeTable, get_keys) {
    UnorderedBTreeTable<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    TVector<int> keys = table.get_keys();

    EXPECT_EQ(keys[0], 1);
    EXPECT_EQ(keys[1], 2);
    EXPECT_EQ(keys[2], 3);
}
