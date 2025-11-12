// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_DSU_DSU_H_
#define LIBS_LIB_DSU_DSU_H_

#include <cstddef>

class DSU {
 private:
    int *_parents, *_ranks;
    size_t _size;

 public:
    explicit DSU(size_t);
    ~DSU();

    void unite(int, int);
    int find(int);

 private:
    int find_recursive(int);
};

#endif  // LIBS_LIB_DSU_DSU_H_
