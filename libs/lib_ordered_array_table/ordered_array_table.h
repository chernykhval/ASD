// Copyright 2026 Chernykh Valentin

#ifndef LIBS_LIB_ORDERED_ARRAY_TABLE_ORDERED_ARRAY_TABLE_H_
#define LIBS_LIB_ORDERED_ARRAY_TABLE_ORDERED_ARRAY_TABLE_H_

#include <sstream>
#include <string>

#include "libs/lib_itable/itable.h"

template <typename Key, typename Value>
class OrderedArrayTable : public ITable<Key, Value> {
 private:
    TVector<std::pair<Key, Value>> _rows;

 public:
    OrderedArrayTable() = default;
    ~OrderedArrayTable() override = default;

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

private:
    size_t find_index(const Key& key, bool& found) const;
};

template<typename Key, typename Value>
void OrderedArrayTable<Key, Value>::insert(const Key& key, const Value& value) {
    bool found = false;
    size_t index = find_index(key, found);

    if (found) {
        throw std::invalid_argument("Key already exists");
    }

    _rows.insert(_rows.begin() + index, {key, value});
}

template<typename Key, typename Value>
bool OrderedArrayTable<Key, Value>::erase(const Key& key) {
    bool found = false;
    size_t index = find_index(key, found);

    if (found) {
        _rows.erase(_rows.begin() + index);
        return true;
    }

    return false;
}

template<typename Key, typename Value>
Value* OrderedArrayTable<Key, Value>::find(const Key& key) {
    bool found = false;
    size_t index = find_index(key, found);

    if (found) {
        return &_rows[index].second;
    }

    return nullptr;
}

template<typename Key, typename Value>
const Value* OrderedArrayTable<Key, Value>::find(const Key& key) const {
    bool found = false;
    size_t index = find_index(key, found);

    if (found) {
        return &_rows[index].second;
    }

    return nullptr;
}

template<typename Key, typename Value>
bool OrderedArrayTable<Key, Value>::is_empty() const {
    return _rows.is_empty();
}

template<typename Key, typename Value>
void OrderedArrayTable<Key, Value>::clear() {
    _rows.clear();
}

template<typename Key, typename Value>
size_t OrderedArrayTable<Key, Value>::size() const {
    return _rows.size();
}

template<typename Key, typename Value>
std::string OrderedArrayTable<Key, Value>::to_string() const {
    std::stringstream ss;

    ss << "{key} : {value}\n";

    for (const auto& row : _rows) {
        ss << "{" << row.first << "} : {" << row.second << "}\n";
    }

    return ss.str();
}

template<typename Key, typename Value>
TVector<Key> OrderedArrayTable<Key, Value>::get_keys() const {
    TVector<Key> keys;

    for (const auto& row : _rows) {
        keys.push_back(row.first);
    }

    return keys;
}

template<typename Key, typename Value>
bool OrderedArrayTable<Key, Value>::contains(const Key& key) const {
    return find(key) != nullptr;
}

template<typename Key, typename Value>
size_t OrderedArrayTable<Key, Value>::find_index(const Key& key, bool& found) const {
    size_t left = 0;
    size_t right = _rows.size();

    while (left < right) {
        size_t middle = left + (right - left) / 2;

        if (_rows[middle].first == key) {
            found = true;
            return middle;
        } else if (_rows[middle].first < key) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    found = false;
    return left;
}

#endif  // LIBS_LIB_ORDERED_ARRAY_TABLE_ORDERED_ARRAY_TABLE_H_
