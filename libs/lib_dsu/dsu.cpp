// Copyright 2025 Chernykh Valentin

#include "libs/lib_dsu/dsu.h"

#include <stdexcept>

DSU::DSU(size_t size) : _size(size) {
    _parents = new int[size];
    _ranks = new int[size];

    for (int i = 0; i < size; i++) {
        _parents[i] = i;
        _ranks[i] = 0;
    }
}

DSU::~DSU() {
    delete[] _parents;
    delete[] _ranks;
}

void DSU::unite(int x, int y) {
    if (x >= _size || y >= _size || x < 0 || y < 0) {
        throw std::out_of_range("DSU::unite()");
    }

    int parent_x = find(x);
    int parent_y = find(y);

    if (_ranks[parent_x] >= _ranks[parent_y]) {
        _parents[parent_y] = parent_x;
    } else {
        _parents[parent_x] = parent_y;
    }

    if (_ranks[parent_x] == _ranks[parent_y]) {
        _ranks[parent_x]++;
    }
}

int DSU::find(int x) {
    if (x >= _size || x < 0) {
        throw std::out_of_range("DSU::find()");
    }

    return find_recursive(x);
}

int DSU::find_recursive(int x) {
    if (_parents[x] == x) {
        return x;
    }

    return _parents[x] = find_recursive(_parents[x]);
}
