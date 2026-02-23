// Copyright 2026 Chernykh Valentin

#include <gtest/gtest.h>
#include <string>
#include "libs/lib_ordered_array_table/ordered_array_table.h"

#define EPSILON 0.000001

TEST(TestOrderedArrayTable, insert) {
    OrderedArrayTable<int, std::string> table;

    table.insert(1, "hello");

    EXPECT_EQ(1, table.size());
}

TEST(TestOrderedArrayTable, insert_exception) {
    OrderedArrayTable<int, std::string> table;

    table.insert(1, "hello");

    EXPECT_THROW(table.insert(1, "hello"), std::invalid_argument);
}

TEST(TestOrderedArrayTable, erase_true) {
    OrderedArrayTable<int, std::string> table;

    table.insert(1, "hello");

    EXPECT_TRUE(table.erase(1));
    EXPECT_FALSE(table.erase(1));
    EXPECT_EQ(0, table.size());
}

TEST(TestOrderedArrayTable, erase_false) {
    OrderedArrayTable<int, std::string> table;

    table.insert(1, "hello");

    EXPECT_FALSE(table.erase(2));
}

TEST(TestOrderedArrayTable, find) {
    OrderedArrayTable<int, std::string> table;

    EXPECT_EQ(nullptr, table.find(1));
    table.insert(1, "hello");
    EXPECT_EQ("hello", *table.find(1));
}

TEST(TestOrderedArrayTable, is_empty_and_clear) {
    OrderedArrayTable<int, std::string> table;

    EXPECT_EQ(true, table.is_empty());
    table.insert(1, "hello");
    EXPECT_EQ(false, table.is_empty());
    table.clear();
    EXPECT_EQ(true, table.is_empty());
}

TEST(TestOrderedArrayTable, multiple_elements_scenario) {
    OrderedArrayTable<int, std::string> table;

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

TEST(TestOrderedArrayTable, to_string) {
    OrderedArrayTable<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    std::string text = "{key} : {value}\n"
                       "{1} : {one}\n"
                       "{2} : {two}\n"
                       "{3} : {three}\n";

    EXPECT_EQ(text, table.to_string());
}

TEST(TestOrderedArrayTable, insert_maintains_order) {
    OrderedArrayTable<int, std::string> table;

    table.insert(3, "three");
    table.insert(1, "one");
    table.insert(4, "four");
    table.insert(2, "two");

    EXPECT_EQ(4, table.size());

    TVector<int> keys = table.get_keys();
    EXPECT_EQ(1, keys[0]);
    EXPECT_EQ(2, keys[1]);
    EXPECT_EQ(3, keys[2]);
    EXPECT_EQ(4, keys[3]);
}

TEST(TestOrderedArrayTable, erase_maintains_order) {
    OrderedArrayTable<int, std::string> table;

    table.insert(10, "A");
    table.insert(30, "C");
    table.insert(20, "B");

    table.erase(20);

    EXPECT_EQ(2, table.size());

    TVector<int> keys = table.get_keys();
    EXPECT_EQ(10, keys[0]);
    EXPECT_EQ(30, keys[1]);
}

TEST(TestOrderedArrayTable, to_string_always_sorted) {
    OrderedArrayTable<int, std::string> table;

    table.insert(3, "three");
    table.insert(2, "two");
    table.insert(1, "one");

    std::string expected_text = "{key} : {value}\n"
                                "{1} : {one}\n"
                                "{2} : {two}\n"
                                "{3} : {three}\n";

    EXPECT_EQ(expected_text, table.to_string());
}
