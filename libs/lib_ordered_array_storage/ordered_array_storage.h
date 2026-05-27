// Copyright 2026 Chernykh Valentin

#ifndef LIBS_LIB_ORDERED_ARRAY_STORAGE_ORDERED_ARRAY_STORAGE_H_
#define LIBS_LIB_ORDERED_ARRAY_STORAGE_ORDERED_ARRAY_STORAGE_H_

#include <stdexcept>
#include "libs/lib_tvector/tvector.h"

template<typename Key, typename Value>
class OrderedArrayStorage {
 private:
    TVector<std::pair<Key, Value>> _data;

    size_t find_index(const Key& key, bool& found) const;

 public:
    void insert(const Key& key, const Value& value);
    bool erase(const Key& key);
    Value* find(const Key& key);
    const Value* find(const Key& key) const;
    bool is_empty() const;
    void clear();
    size_t size() const;
    TVector<Key> get_keys() const;
};

template<typename Key, typename Value>
size_t OrderedArrayStorage<Key, Value>::find_index(const Key& key, bool& found) const {
    size_t left = 0;
    size_t right = _data.size();

    while (left < right) {
        size_t middle = left + (right - left) / 2;

        if (_data[middle].first == key) {
            found = true;
            return middle;
        } else if (_data[middle].first < key) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    found = false;
    return left;
}

template<typename Key, typename Value>
void OrderedArrayStorage<Key, Value>::insert(const Key& key, const Value& value) {
    bool found = false;
    size_t index = find_index(key, found);

    if (found) {
        throw std::invalid_argument("Key already exists");
    }

    _data.insert(_data.begin() + index, {key, value});
}

template<typename Key, typename Value>
bool OrderedArrayStorage<Key, Value>::erase(const Key& key) {
    bool found = false;
    size_t index = find_index(key, found);

    if (found) {
        _data.erase(_data.begin() + index);
        return true;
    }

    return false;
}

template<typename Key, typename Value>
Value* OrderedArrayStorage<Key, Value>::find(const Key& key) {
    bool found = false;
    size_t index = find_index(key, found);

    if (found) return &_data[index].second;
    return nullptr;
}

template<typename Key, typename Value>
const Value* OrderedArrayStorage<Key, Value>::find(const Key& key) const {
    bool found = false;
    size_t index = find_index(key, found);

    if (found) return &_data[index].second;
    return nullptr;
}

template<typename Key, typename Value>
bool OrderedArrayStorage<Key, Value>::is_empty() const {
    return _data.is_empty();
}

template<typename Key, typename Value>
void OrderedArrayStorage<Key, Value>::clear() {
    _data.clear();
}

template<typename Key, typename Value>
size_t OrderedArrayStorage<Key, Value>::size() const {
    return _data.size();
}

template<typename Key, typename Value>
TVector<Key> OrderedArrayStorage<Key, Value>::get_keys() const {
    TVector<Key> keys;
    for (const auto& p : _data) {
        keys.push_back(p.first);
    }
    return keys;
}

#endif  // LIBS_LIB_ORDERED_ARRAY_STORAGE_ORDERED_ARRAY_STORAGE_H_
