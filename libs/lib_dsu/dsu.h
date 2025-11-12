// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_DSU_DSU_H_
#define LIBS_LIB_DSU_DSU_H_

#include <cstddef>

class DSU {
 private:
    int *_parents, *_ranks;
    size_t _size, _count;

 public:
    explicit DSU(size_t);
    ~DSU() noexcept;

    void unite(int, int);
    int find(int);
    int count() const noexcept;

 private:
    int find_recursive(int);
};

#endif  // LIBS_LIB_DSU_DSU_H_
