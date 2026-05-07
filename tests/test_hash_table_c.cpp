// Copyright 2026 Chernykh Valentin

#include <gtest/gtest.h>
#include <string>
#include "libs/lib_hash_table_c/hash_table_c.h"

TEST(TestHashTableC, is_empty_on_new_table) {
    HashTableC<int> table;
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(0, table.size());
}

TEST(TestHashTableC, insert_increases_size) {
    HashTableC<int> table;
    table.insert("key", 1);
    EXPECT_EQ(1, table.size());
    EXPECT_FALSE(table.is_empty());
}

TEST(TestHashTableC, insert_duplicate_throws) {
    HashTableC<int> table;
    table.insert("key", 1);
    EXPECT_THROW(table.insert("key", 2), std::invalid_argument);
    EXPECT_EQ(1, table.size());
}

TEST(TestHashTableC, find_returns_nullptr_when_missing) {
    HashTableC<int> table;
    EXPECT_EQ(nullptr, table.find("missing"));
}

TEST(TestHashTableC, find_returns_value) {
    HashTableC<int> table;
    table.insert("hello", 42);
    EXPECT_EQ(42, *table.find("hello"));
}

TEST(TestHashTableC, find_allows_modify) {
    HashTableC<int> table;
    table.insert("x", 1);
    *table.find("x") = 99;
    EXPECT_EQ(99, *table.find("x"));
}

TEST(TestHashTableC, erase_returns_true_when_found) {
    HashTableC<int> table;
    table.insert("key", 1);
    EXPECT_TRUE(table.erase("key"));
}

TEST(TestHashTableC, erase_returns_false_when_missing) {
    HashTableC<int> table;
    EXPECT_FALSE(table.erase("missing"));
}

TEST(TestHashTableC, erase_decreases_size) {
    HashTableC<int> table;
    table.insert("a", 1);
    table.insert("b", 2);
    table.erase("a");
    EXPECT_EQ(1, table.size());
    EXPECT_EQ(nullptr, table.find("a"));
    EXPECT_EQ(2, *table.find("b"));
}

TEST(TestHashTableC, erase_then_insert_same_key) {
    HashTableC<int> table;
    table.insert("key", 1);
    table.erase("key");
    table.insert("key", 2);
    EXPECT_EQ(2, *table.find("key"));
}

TEST(TestHashTableC, clear_empties_table) {
    HashTableC<int> table;
    table.insert("a", 1);
    table.insert("b", 2);
    table.clear();
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(0, table.size());
}

TEST(TestHashTableC, clear_then_insert_works) {
    HashTableC<int> table;
    table.insert("a", 1);
    table.clear();
    table.insert("b", 2);
    EXPECT_EQ(1, table.size());
    EXPECT_EQ(2, *table.find("b"));
}

TEST(TestHashTableC, contains_existing_key) {
    HashTableC<int> table;
    table.insert("hello", 1);
    EXPECT_TRUE(table.contains("hello"));
}

TEST(TestHashTableC, contains_missing_key) {
    HashTableC<int> table;
    EXPECT_FALSE(table.contains("missing"));
}

TEST(TestHashTableC, get_keys_returns_all_keys) {
    HashTableC<int> table;
    table.insert("a", 1);
    table.insert("b", 2);
    table.insert("c", 3);
    TVector<std::string> keys = table.get_keys();
    EXPECT_EQ(3, keys.size());
    EXPECT_TRUE(table.contains("a"));
    EXPECT_TRUE(table.contains("b"));
    EXPECT_TRUE(table.contains("c"));
}

TEST(TestHashTableC, collisions_handled_correctly) {
    // "abc" и "bca" имеют одинаковый хэш (сумма ASCII одинакова)
    HashTableC<int> table;
    table.insert("abc", 1);
    table.insert("bca", 2);
    table.insert("cab", 3);
    EXPECT_EQ(3, table.size());
    EXPECT_EQ(1, *table.find("abc"));
    EXPECT_EQ(2, *table.find("bca"));
    EXPECT_EQ(3, *table.find("cab"));
}

TEST(TestHashTableC, erase_one_of_colliding_keys) {
    HashTableC<int> table;
    table.insert("abc", 1);
    table.insert("bca", 2);
    table.erase("abc");
    EXPECT_EQ(nullptr, table.find("abc"));
    EXPECT_EQ(2, *table.find("bca"));
    EXPECT_EQ(1, table.size());
}

TEST(TestHashTableC, contains_after_erase) {
    HashTableC<int> table;
    table.insert("key", 1);
    EXPECT_TRUE(table.contains("key"));
    table.erase("key");
    EXPECT_FALSE(table.contains("key"));
}

TEST(TestHashTableC, to_string_empty) {
    HashTableC<int> table;
    EXPECT_EQ("{key} : {value}\n", table.to_string());
}

TEST(TestHashTableC, to_string_single_element) {
    HashTableC<int> table;
    table.insert("hello", 42);
    EXPECT_EQ("{key} : {value}\n{hello} : {42}\n", table.to_string());
}

TEST(TestHashTableC, multiple_elements_scenario) {
    HashTableC<std::string> table;
    table.insert("one", "first");
    table.insert("two", "second");
    table.insert("three", "third");

    EXPECT_EQ(3, table.size());
    EXPECT_EQ("first", *table.find("one"));
    EXPECT_EQ("second", *table.find("two"));
    EXPECT_EQ("third", *table.find("three"));

    table.erase("two");

    EXPECT_EQ(2, table.size());
    EXPECT_EQ(nullptr, table.find("two"));
    EXPECT_EQ("first", *table.find("one"));
    EXPECT_EQ("third", *table.find("three"));
}
