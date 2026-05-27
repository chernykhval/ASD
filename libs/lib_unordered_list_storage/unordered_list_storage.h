// Copyright 2026 Chernykh Valentin

#ifndef LIBS_LIB_UNORDERED_LIST_STORAGE_UNORDERED_LIST_STORAGE_H_
#define LIBS_LIB_UNORDERED_LIST_STORAGE_UNORDERED_LIST_STORAGE_H_

#include <stdexcept>
#include "libs/lib_list/list.h"
#include "libs/lib_tvector/tvector.h"

template<typename Key, typename Value>
class UnorderedListStorage {
 private:
    List<std::pair<Key, Value>> _data;

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
void UnorderedListStorage<Key, Value>::insert(const Key& key, const Value& value) {
    if (find(key) != nullptr) {
        throw std::invalid_argument("Key already exists");
    }
    _data.push_back({key, value});
}

template<typename Key, typename Value>
bool UnorderedListStorage<Key, Value>::erase(const Key& key) {
    for (auto it = _data.begin(); it != _data.end(); ++it) {
        if (it->first == key) {
            _data.erase(it);
            return true;
        }
    }
    return false;
}

template<typename Key, typename Value>
Value* UnorderedListStorage<Key, Value>::find(const Key& key) {
    for (auto& p : _data) {
        if (p.first == key) return &p.second;
    }
    return nullptr;
}

template<typename Key, typename Value>
const Value* UnorderedListStorage<Key, Value>::find(const Key& key) const {
    for (const auto& p : _data) {
        if (p.first == key) return &p.second;
    }
    return nullptr;
}

template<typename Key, typename Value>
bool UnorderedListStorage<Key, Value>::is_empty() const {
    return _data.is_empty();
}

template<typename Key, typename Value>
void UnorderedListStorage<Key, Value>::clear() {
    _data.clear();
}

template<typename Key, typename Value>
size_t UnorderedListStorage<Key, Value>::size() const {
    return _data.size();
}

template<typename Key, typename Value>
TVector<Key> UnorderedListStorage<Key, Value>::get_keys() const {
    TVector<Key> keys;
    for (const auto& p : _data) {
        keys.push_back(p.first);
    }
    return keys;
}

#endif  // LIBS_LIB_UNORDERED_LIST_STORAGE_UNORDERED_LIST_STORAGE_H_
