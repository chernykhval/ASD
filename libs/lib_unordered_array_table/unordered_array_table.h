// Copyright 2026 Chernykh Valentin

#ifndef LIBS_LIB_UNORDERED_ARRAY_TABLE_UNORDERED_ARRAY_TABLE_H_
#define LIBS_LIB_UNORDERED_ARRAY_TABLE_UNORDERED_ARRAY_TABLE_H_

#include <sstream>
#include <string>

#include "libs/lib_itable/itable.h"
#include "libs/lib_tvector/tvector.h"

template <typename Key, typename Value>
class UnorderedArrayTable : public ITable<Key, Value>{
 private:
    TVector<std::pair<Key, Value>> rows;

 public:
    UnorderedArrayTable() = default;
    ~UnorderedArrayTable() override = default;

    void insert(const Key& key, const Value& value) override;
    void erase(const Key& key) override;
    Value* find(const Key& key) override;
    const Value* find(const Key& key) const override;
    bool is_empty() const override;
    void clear() override;
    size_t size() const override;
    std::string to_string() const override;
    TVector<Key> get_keys() const override;
    bool contains(const Key& key) const override;
};

template<typename Key, typename Value>
void UnorderedArrayTable<Key, Value>::
insert(const Key& key, const Value& value) {
    for (auto& row : rows) {
        if (row.first == key) {
            // row.second = value;
            // return;
            throw std::invalid_argument("Key already exists");
        }
    }

    rows.push_back(std::pair<Key, Value>(key, value));
}

template<typename Key, typename Value>
void UnorderedArrayTable<Key, Value>::erase(const Key& key) {
    for (auto it = rows.begin(); it != rows.end(); ++it) {
        if (it->first == key) {
            rows.erase(it);
            return;
        }
    }

    throw std::invalid_argument("Key not found");
}

template<typename Key, typename Value>
Value* UnorderedArrayTable<Key, Value>::find(const Key& key) {
    for (auto& row : rows) {
        if (row.first == key) {
            return &row.second;
        }
    }

    return nullptr;
}

template<typename Key, typename Value>
const Value* UnorderedArrayTable<Key, Value>::find(const Key& key) const {
    for (const auto& row : rows) {
        if (row.first == key) {
            return &row.second;
        }
    }

    return nullptr;
}

template<typename Key, typename Value>
bool UnorderedArrayTable<Key, Value>::is_empty() const {
    return rows.is_empty();
}

template<typename Key, typename Value>
void UnorderedArrayTable<Key, Value>::clear() {
    rows.clear();
}

template<typename Key, typename Value>
size_t UnorderedArrayTable<Key, Value>::size() const {
    return rows.size();
}

template<typename Key, typename Value>
std::string UnorderedArrayTable<Key, Value>::to_string() const {
    std::stringstream ss;

    ss << "{key} : {value}\n";

    for (const auto& row : rows) {
        ss << "{" << row.first << "} : {" << row.second << "}\n";
    }

    return ss.str();
}

template<typename Key, typename Value>
TVector<Key> UnorderedArrayTable<Key, Value>::get_keys() const {
    TVector<Key> keys;

    for (const auto& row : rows) {
        keys.push_back(row.first);
    }

    return keys;
}

template<typename Key, typename Value>
bool UnorderedArrayTable<Key, Value>::contains(const Key& key) const {
    return find(key) != nullptr;
}


#endif  // LIBS_LIB_UNORDERED_ARRAY_TABLE_UNORDERED_ARRAY_TABLE_H_
