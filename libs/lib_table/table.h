// Copyright 2026 Chernykh Valentin

#ifndef LIBS_LIB_TABLE_TABLE_H_
#define LIBS_LIB_TABLE_TABLE_H_

#include <sstream>
#include "libs/lib_itable/itable.h"
#include "libs/lib_tvector/tvector.h"

template<typename Storage, typename Key, typename Value>
class Table : public ITable<Key, Value> {
 private:
    Storage _storage;

 public:
    Table() = default;
    ~Table() override = default;

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

template<typename Storage, typename Key, typename Value>
void Table<Storage, Key, Value>::insert(const Key& key, const Value& value) {
    _storage.insert(key, value);
}

template<typename Storage, typename Key, typename Value>
bool Table<Storage, Key, Value>::erase(const Key& key) {
    if (_storage.find(key) == nullptr) return false;
    _storage.erase(key);
    return true;
}

template<typename Storage, typename Key, typename Value>
Value* Table<Storage, Key, Value>::find(const Key& key) {
    return _storage.find(key);
}

template<typename Storage, typename Key, typename Value>
const Value* Table<Storage, Key, Value>::find(const Key& key) const {
    return _storage.find(key);
}

template<typename Storage, typename Key, typename Value>
bool Table<Storage, Key, Value>::is_empty() const {
    return _storage.is_empty();
}

template<typename Storage, typename Key, typename Value>
void Table<Storage, Key, Value>::clear() {
    _storage.clear();
}

template<typename Storage, typename Key, typename Value>
size_t Table<Storage, Key, Value>::size() const {
    return _storage.size();
}

template<typename Storage, typename Key, typename Value>
std::string Table<Storage, Key, Value>::to_string() const {
    if (is_empty()) {
        return "Table is empty\n";
    }

    TVector<Key> keys = _storage.get_keys();
    std::stringstream ss;

    ss << "{key} : {value}\n";

    for (size_t i = 0; i < keys.size(); i++) {
        ss << "{" << keys[i] << "} : {" << *_storage.find(keys[i]) << "}\n";
    }

    return ss.str();
}

template<typename Storage, typename Key, typename Value>
TVector<Key> Table<Storage, Key, Value>::get_keys() const {
    return _storage.get_keys();
}

template<typename Storage, typename Key, typename Value>
bool Table<Storage, Key, Value>::contains(const Key& key) const {
    return _storage.find(key) != nullptr;
}

#endif  // LIBS_LIB_TABLE_TABLE_H_
