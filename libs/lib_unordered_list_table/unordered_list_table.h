// Copyright 2026 Chernykh Valentin

#ifndef LIBS_LIB_UNORDERED_LIST_TABLE_UNORDERED_LIST_TABLE_H_
#define LIBS_LIB_UNORDERED_LIST_TABLE_UNORDERED_LIST_TABLE_H_

#include <string>
#include <sstream>

#include "libs/lib_list/list.h"
#include "libs/lib_itable/itable.h"

template <typename Key, typename Value>
class UnorderedListTable : public ITable<Key, Value> {
 private:
    List<std::pair<Key, Value>> _rows;

 public:
    UnorderedListTable() = default;
    ~UnorderedListTable() override = default;

    void insert(const Key& key, const Value& value) override;
    bool erase(const Key& key) override;
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
void UnorderedListTable<Key, Value>::insert(const Key& key, const Value& value) {
    if (contains(key)) {
        throw std::invalid_argument("Key already exists");
    }

    _rows.push_back({key, value});
}

template<typename Key, typename Value>
bool UnorderedListTable<Key, Value>::erase(const Key& key) {
    for (auto it = _rows.begin(); it != _rows.end(); ++it) {
        if (it->first == key) {
            _rows.erase(it);
            return true;
        }
    }

    return false;
}

template<typename Key, typename Value>
Value* UnorderedListTable<Key, Value>::find(const Key& key) {
    for (auto& row : _rows) {
        if (row.first == key) {
            return &row.second;
        }
    }

    return nullptr;
}

template<typename Key, typename Value>
const Value* UnorderedListTable<Key, Value>::find(const Key& key) const {
    for (const auto& row : _rows) {
        if (row.first == key) {
            return &row.second;
        }
    }

    return nullptr;
}

template<typename Key, typename Value>
bool UnorderedListTable<Key, Value>::is_empty() const {
    return _rows.is_empty();
}

template<typename Key, typename Value>
void UnorderedListTable<Key, Value>::clear() {
}

template<typename Key, typename Value>
size_t UnorderedListTable<Key, Value>::size() const {
    return _rows.size();
}

template<typename Key, typename Value>
std::string UnorderedListTable<Key, Value>::to_string() const {
    std::stringstream ss;

    ss << "{key} : {value}\n";

    for (const auto& row : _rows) {
        ss << "{" << row.first << "} : {" << row.second << "}\n";
    }

    return ss.str();
}

template<typename Key, typename Value>
TVector<Key> UnorderedListTable<Key, Value>::get_keys() const {
    TVector<Key> keys;

    for (const auto& row : _rows) {
        keys.push_back(row.first);
    }

    return keys;
}

template<typename Key, typename Value>
bool UnorderedListTable<Key, Value>::contains(const Key& key) const {
    return find(key) != nullptr;
}

#endif  // LIBS_LIB_UNORDERED_LIST_TABLE_UNORDERED_LIST_TABLE_H_
