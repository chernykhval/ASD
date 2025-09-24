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

    size_t rows() const;
    size_t cols() const;

    MVector<T>& operator[](size_t index);
    const MVector<T>& operator[](size_t index) const;
};

template<typename T>
Matrix<T>::Matrix() : _rows(0), _cols(0) {}

template<typename T>
Matrix<T>::Matrix(size_t rows, size_t cols) : _rows(rows), _cols(cols) {}

template<typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> init) {
    _rows = init.size();

    if (_rows > 0) {
        _cols = init.begin()->size();
    } else {
        _cols = 0;
    }

    for (const auto& row : init) {
        if (row.size() != _cols) {
            throw std::invalid_argument("Matrix: All rows"
                                        " must have the same length");
        }
    }

    _data = MVector<MVector<T>>(_rows);
    size_t i = 0;

    for (const auto& row_list : init) {
        _data[i] = MVector<T>(row_list);
        ++i;
    }
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& other) :
_rows(other._rows), _cols(other._cols), _data(other._data) {}

template<typename T>
size_t Matrix<T>::rows() const {
    return _rows;
}

template<typename T>
size_t Matrix<T>::cols() const {
    return _cols;
}

template<typename T>
MVector<T>& Matrix<T>::operator[](size_t index) {
    return _data[index];
}

template<typename T>
const MVector<T>& Matrix<T>::operator[](size_t index) const {
    return _data[index];
}

#endif  // LIBS_LIB_MATRIX_MATRIX_H_
