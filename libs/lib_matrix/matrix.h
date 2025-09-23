// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_MATRIX_MATRIX_H_
#define LIBS_LIB_MATRIX_MATRIX_H_

#include "libs/lib_mvector/mvector.h"

template<typename T>
class Matrix {
 private:
    size_t _rows, _cols;
    MVector<MVector<T>> _data;
 public:
    Matrix();
    Matrix(size_t, size_t);
    Matrix(std::initializer_list<std::initializer_list<T>>);
    Matrix(const Matrix<T>&);
};

template<typename T>
Matrix<T>::Matrix() : _rows(0), _cols(0) {}

template<typename T>
Matrix<T>::Matrix(size_t rows, size_t cols) : _rows(rows), _cols(cols) {}

template<typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> init) :
_rows(0), _cols(0), _data(init) {}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& other) :
_rows(other._rows), _cols(other._cols), _data(other._data) {}


#endif  // LIBS_LIB_MATRIX_MATRIX_H_
