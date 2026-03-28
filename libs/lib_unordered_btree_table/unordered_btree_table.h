// Copyright 2026 Chernykh Valentin

#ifndef LIBS_LIB_UNORDERED_BTREE_TABLE_UNORDERED_BTREE_TABLE_H_
#define LIBS_LIB_UNORDERED_BTREE_TABLE_UNORDERED_BTREE_TABLE_H_

#include <sstream>

#include "libs/lib_btree/btree.h"
#include "libs/lib_itable/itable.h"
#include "libs/lib_tvector/tvector.h"

template <typename Key, typename Value>
class UnorderedBTreeTable : public ITable<Key, Value> {
 private:
    BTree<Key, Value> _tree;

 public:
    UnorderedBTreeTable() = default;
    ~UnorderedBTreeTable() override = default;

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
void UnorderedBTreeTable<Key, Value>::insert(const Key& key, const Value& value) {
    _tree.insert(key, value);
}

template<typename Key, typename Value>
bool UnorderedBTreeTable<Key, Value>::erase(const Key& key) {
    try {
        _tree.erase(key);
        return true;
    }
    catch (const std::exception& ex) {
        return false;
    }
}

template<typename Key, typename Value>
Value* UnorderedBTreeTable<Key, Value>::find(const Key& key) {
    return _tree.find(key);
}

template<typename Key, typename Value>
const Value* UnorderedBTreeTable<Key, Value>::find(const Key& key) const {
    return _tree.find(key);
}

template<typename Key, typename Value>
bool UnorderedBTreeTable<Key, Value>::is_empty() const {
    return _tree.is_empty();
}

template<typename Key, typename Value>
void UnorderedBTreeTable<Key, Value>::clear() {
    _tree.clear();
}

template<typename Key, typename Value>
size_t UnorderedBTreeTable<Key, Value>::size() const {
    return _tree.size();
}

template<typename Key, typename Value>
std::string UnorderedBTreeTable<Key, Value>::to_string() const {
    if (is_empty()) {
       return "Table is empty\n";
    }

    TVector<Key> keys = _tree.get_keys();

    std::stringstream ss;

    ss << "{key} : {value}\n";

    for (int i = 0; i < _tree.size(); i++) {
        ss << "{" << keys[i] << "} : {" << *_tree.find(keys[i]) << "}\n";
    }

    return ss.str();
}

template<typename Key, typename Value>
TVector<Key> UnorderedBTreeTable<Key, Value>::get_keys() const {
    return _tree.get_keys();
}

template<typename Key, typename Value>
bool UnorderedBTreeTable<Key, Value>::contains(const Key& key) const {
    return _tree.find(key) != nullptr;
}

#endif  // LIBS_LIB_UNORDERED_BTREE_TABLE_UNORDERED_BTREE_TABLE_H_
