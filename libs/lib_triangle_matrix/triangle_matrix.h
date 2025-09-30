// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_TRIANGLE_MATRIX_TRIANGLE_MATRIX_H_
#define LIBS_LIB_TRIANGLE_MATRIX_TRIANGLE_MATRIX_H_

#include "libs/lib_mvector/mvector.h"

template<typename T>
class TriangleMatrix {
 private:
    size_t _size;
    MVector<MVector<T>> _data;

 public:
    TriangleMatrix();
    explicit TriangleMatrix(size_t size);
    TriangleMatrix(std::initializer_list<std::initializer_list<T>>);
    TriangleMatrix(const TriangleMatrix&);

    size_t dim() const;
};

template<typename T>
TriangleMatrix<T>::TriangleMatrix() : _size(0), _data() {}

template<typename T>
TriangleMatrix<T>::TriangleMatrix(size_t size) : _size(size) {
    _data = MVector<MVector<T>>(size);

    for (size_t i = 0; i < size; i++) {
        _data[i] = MVector<T>(size - i);
    }
}

template<typename T>
size_t TriangleMatrix<T>::dim() const {
    return _size;
}

#endif  // LIBS_LIB_TRIANGLE_MATRIX_TRIANGLE_MATRIX_H_
