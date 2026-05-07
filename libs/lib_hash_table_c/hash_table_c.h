// Copyright 2026 Chernykh Valentin

#ifndef LIBS_LIB_HASH_TABLE_C_HASH_TABLE_C_H_
#define LIBS_LIB_HASH_TABLE_C_HASH_TABLE_C_H_

#include <string>
#include <sstream>
#include "libs/lib_itable/itable.h"
#include "libs/lib_list/list.h"
#include "libs/lib_tvector/tvector.h"

template<typename Value>
class HashTableC : public ITable<std::string, Value> {
 private:
    struct HashData {
        std::string key;
        Value value;

        HashData(std::string _key, Value _value) : key(_key), value(_value) {}
    };

    size_t _chains_count;
    size_t _elements_count;
    TVector<List<HashData>> _chains;

public:
    explicit HashTableC(size_t chains_count = 10);

    void insert(const std::string& key, const Value& value) override;
    bool erase(const std::string& key) override;
    Value* find(const std::string& key) override;
    const Value* find(const std::string& key) const override;
    bool is_empty() const noexcept override;
    void clear() override;
    size_t size() const noexcept override;
    std::string to_string() const override;
    TVector<std::string> get_keys() const override;
    bool contains(const std::string& key) const override;

private:
    size_t h(const std::string& key) const noexcept;
};

template<typename Value>
HashTableC<Value>::HashTableC(size_t chains_count)
: _chains_count(chains_count), _elements_count(0) {
    for (size_t i = 0; i < chains_count; i++) {
        _chains.push_back(List<HashData>());
    }
}

template<typename Value>
void HashTableC<Value>::insert(const std::string& key, const Value& value) {
    size_t hash = h(key);

    for (auto data : _chains[hash]) {
        if (data.key == key) {
            throw std::invalid_argument("Key already exists");
        }
    }

    _chains[hash].push_back(HashData(key, value));
    _elements_count++;
}

template<typename Value>
bool HashTableC<Value>::erase(const std::string& key) {
    size_t hash = h(key);

    for (auto it = _chains[hash].begin(); it != _chains[hash].end(); it++) {
        if (it->key == key) {
            _chains[hash].erase(it);
            _elements_count--;
            return true;
        }
    }

    return false;
}

template<typename Value>
Value* HashTableC<Value>::find(const std::string& key) {
    size_t hash = h(key);

    for (auto it = _chains[hash].begin(); it != _chains[hash].end(); it++) {
        if (it->key == key) {
            return &(it->value);
        }
    }

    return nullptr;
}

template<typename Value>
const Value* HashTableC<Value>::find(const std::string& key) const {
    size_t hash = h(key);

    for (auto it = _chains[hash].begin(); it != _chains[hash].end(); it++) {
        if (it->key == key) {
            return &(it->value);
        }
    }

    return nullptr;
}

template<typename Value>
bool HashTableC<Value>::is_empty() const noexcept {
    return _elements_count == 0;
}

template<typename Value>
void HashTableC<Value>::clear() {
    for (size_t i = 0; i < _chains_count; i++) {
        _chains[i].clear();
    }
    _elements_count = 0;
}

template<typename Value>
size_t HashTableC<Value>::size() const noexcept {
    return _elements_count;
}

template<typename Value>
TVector<std::string> HashTableC<Value>::get_keys() const {
    TVector<std::string> vec;
    for (size_t i = 0; i < _chains_count; i++) {
        for (auto data : _chains[i]) {
            vec.push_back(data.key);
        }
    }
    return vec;
}

template<typename Value>
bool HashTableC<Value>::contains(const std::string& key) const {
    return find(key) != nullptr;
}

template<typename Value>
std::string HashTableC<Value>::to_string() const {
    std::stringstream ss;

    ss << "{key} : {value}\n";

    for (size_t i = 0; i < _chains_count; i++) {
        for (auto data : _chains[i]) {
            ss << "{" << data.key << "} : {" << data.value << "}\n";
        }
    }

    return ss.str();
}

template<typename Value>
size_t HashTableC<Value>::h(const std::string& key) const noexcept {
    size_t hash = 0;

    for (auto l : key) {
        hash += l;
    }

    hash %= _chains_count;

    return hash;
}

#endif  // LIBS_LIB_HASH_TABLE_C_HASH_TABLE_C_H_
