// Copyright 2026 Chernykh Valentin

#include <gtest/gtest.h>
#include <string>
#include "libs/lib_hash_table_oa/hash_table_oa.h"

TEST(TestHashTableOA, is_empty_on_new_table) {
    HashTableOA<int> table;
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(0, table.size());
}

TEST(TestHashTableOA, insert_increases_size) {
    HashTableOA<int> table;
    table.insert("key", 1);
    EXPECT_EQ(1, table.size());
    EXPECT_FALSE(table.is_empty());
}

TEST(TestHashTableOA, insert_duplicate_throws) {
    HashTableOA<int> table;
    table.insert("key", 1);
    EXPECT_THROW(table.insert("key", 2), std::invalid_argument);
    EXPECT_EQ(1, table.size());
}

TEST(TestHashTableOA, find_returns_nullptr_when_missing) {
    HashTableOA<int> table;
    EXPECT_EQ(nullptr, table.find("missing"));
}

TEST(TestHashTableOA, find_returns_value) {
    HashTableOA<int> table;
    table.insert("hello", 42);
    EXPECT_EQ(42, *table.find("hello"));
}

TEST(TestHashTableOA, find_allows_modify) {
    HashTableOA<int> table;
    table.insert("x", 1);
    *table.find("x") = 99;
    EXPECT_EQ(99, *table.find("x"));
}

TEST(TestHashTableOA, erase_returns_true_when_found) {
    HashTableOA<int> table;
    table.insert("key", 1);
    EXPECT_TRUE(table.erase("key"));
}

TEST(TestHashTableOA, erase_returns_false_when_missing) {
    HashTableOA<int> table;
    EXPECT_FALSE(table.erase("missing"));
}

TEST(TestHashTableOA, erase_decreases_size) {
    HashTableOA<int> table;
    table.insert("a", 1);
    table.insert("b", 2);
    table.erase("a");
    EXPECT_EQ(1, table.size());
    EXPECT_EQ(nullptr, table.find("a"));
    EXPECT_EQ(2, *table.find("b"));
}

TEST(TestHashTableOA, erase_then_insert_same_key) {
    HashTableOA<int> table;
    table.insert("key", 1);
    table.erase("key");
    table.insert("key", 2);
    EXPECT_EQ(2, *table.find("key"));
}

TEST(TestHashTableOA, clear_empties_table) {
    HashTableOA<int> table;
    table.insert("a", 1);
    table.insert("b", 2);
    table.clear();
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(0, table.size());
}

TEST(TestHashTableOA, clear_then_insert_works) {
    HashTableOA<int> table;
    table.insert("a", 1);
    table.clear();
    table.insert("b", 2);
    EXPECT_EQ(1, table.size());
    EXPECT_EQ(2, *table.find("b"));
}

TEST(TestHashTableOA, contains_existing_key) {
    HashTableOA<int> table;
    table.insert("hello", 1);
    EXPECT_TRUE(table.contains("hello"));
}

TEST(TestHashTableOA, contains_missing_key) {
    HashTableOA<int> table;
    EXPECT_FALSE(table.contains("missing"));
}

TEST(TestHashTableOA, contains_after_erase) {
    HashTableOA<int> table;
    table.insert("key", 1);
    EXPECT_TRUE(table.contains("key"));
    table.erase("key");
    EXPECT_FALSE(table.contains("key"));
}

TEST(TestHashTableOA, get_keys_returns_all_keys) {
    HashTableOA<int> table;
    table.insert("a", 1);
    table.insert("b", 2);
    table.insert("c", 3);
    TVector<std::string> keys = table.get_keys();
    EXPECT_EQ(3, keys.size());
    EXPECT_TRUE(table.contains("a"));
    EXPECT_TRUE(table.contains("b"));
    EXPECT_TRUE(table.contains("c"));
}

TEST(TestHashTableOA, to_string_empty) {
    HashTableOA<int> table;
    EXPECT_EQ("{key} : {value}\n", table.to_string());
}

TEST(TestHashTableOA, to_string_single_element) {
    HashTableOA<int> table(100);
    table.insert("hello", 42);
    EXPECT_EQ("{key} : {value}\n{hello} : {42}\n", table.to_string());
}

// "abc", "bca", "cab" имеют одинаковый хэш — тест открытой адресации
TEST(TestHashTableOA, collisions_handled_correctly) {
    HashTableOA<int> table;
    table.insert("abc", 1);
    table.insert("bca", 2);
    table.insert("cab", 3);
    EXPECT_EQ(3, table.size());
    EXPECT_EQ(1, *table.find("abc"));
    EXPECT_EQ(2, *table.find("bca"));
    EXPECT_EQ(3, *table.find("cab"));
}

// После удаления одного из коллизионных ключей остальные должны находиться
TEST(TestHashTableOA, find_after_erase_in_collision_chain) {
    HashTableOA<int> table;
    table.insert("abc", 1);
    table.insert("bca", 2);
    table.erase("abc");
    EXPECT_EQ(nullptr, table.find("abc"));
    EXPECT_EQ(2, *table.find("bca"));
}

// Вставка дубликата через DELETED слот не должна создавать дубликат
TEST(TestHashTableOA, no_duplicate_through_deleted_slot) {
    HashTableOA<int> table;
    table.insert("abc", 1);  // слот X
    table.insert("bca", 2);  // слот X+shift (коллизия)
    table.erase("abc");      // слот X → DELETED
    EXPECT_THROW(table.insert("bca", 3), std::invalid_argument);
    EXPECT_EQ(1, table.size());
    EXPECT_EQ(2, *table.find("bca"));
}

TEST(TestHashTableOA, insert_throws_when_full) {
    HashTableOA<int> table(3);
    table.insert("a", 1);
    table.insert("b", 2);
    table.insert("c", 3);
    EXPECT_THROW(table.insert("d", 4), std::out_of_range);
}

TEST(TestHashTableOA, two_dicts_with_overlapping_keys) {
    HashTableOA<int> table;

    table.insert("table", 1349);
    table.insert("hash", 1985);
    table.insert("list", 4372);

    // "list" и "hash" уже есть — исключения глотаем как в main()
    try { table.insert("array", 4312); } catch (...) {}
    try { table.insert("list", 5863); } catch (...) {}
    try { table.insert("hash", 4372); } catch (...) {}
    try { table.insert("vector", 2586); } catch (...) {}

    EXPECT_EQ(5, table.size());
    EXPECT_EQ(1349, *table.find("table"));
    EXPECT_EQ(1985, *table.find("hash"));
    EXPECT_EQ(4372, *table.find("list"));
    EXPECT_EQ(4312, *table.find("array"));
    EXPECT_EQ(2586, *table.find("vector"));
}

TEST(TestHashTableOA, multiple_elements_scenario) {
    HashTableOA<std::string> table;
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
