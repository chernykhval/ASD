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

    bool operator==(const TriangleMatrix<T>&) const;
    bool operator!=(const TriangleMatrix<T>&) const;

    TriangleMatrix<T>& operator=(const TriangleMatrix<T>&);

    TriangleMatrix<T> operator+(const TriangleMatrix<T>&) const;
    TriangleMatrix<T> operator-(const TriangleMatrix<T>&) const;
    TriangleMatrix<T> operator*(const TriangleMatrix<T>&) const;

    TriangleMatrix<T>& operator+=(const TriangleMatrix<T>&);
    TriangleMatrix<T>& operator-=(const TriangleMatrix<T>&);
    TriangleMatrix<T>& operator*=(const TriangleMatrix<T>&);
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
TriangleMatrix<T>::
TriangleMatrix(std::initializer_list<std::initializer_list<T>> init) {
    _size = init.size();
    size_t expected_length = _size;

    for (const auto& row : init) {
        if (row.size() != expected_length) {
            throw std::invalid_argument("TriangleMatrix: All rows must have"
                                        " a decreasing length from size to 1.");
        }

        expected_length--;
    }

    _data = MVector<MVector<T>>(_size);
    size_t i = 0;

    for (const auto& row_list : init) {
        _data[i] = MVector<T>(row_list);
        i++;
    }
}

template<typename T>
TriangleMatrix<T>::TriangleMatrix(const TriangleMatrix& other) :
_size(other._size), _data(other._data) {
}

template<typename T>
size_t TriangleMatrix<T>::dim() const {
    return _size;
}

template<typename T>
bool TriangleMatrix<T>::operator==(const TriangleMatrix<T>& other) const {
    if (_size != other._size) {
        return false;
    }

    for (size_t i = 0; i < _size; i++) {
        if (_data[i] != other._data[i]) {
            return false;
        }
    }

    return true;
}

template<typename T>
bool TriangleMatrix<T>::operator!=(const TriangleMatrix<T>& other) const {
    return !(*this == other);
}

template<typename T>
TriangleMatrix<T>& TriangleMatrix<T>::operator=(const TriangleMatrix<T>& other) {
    if (this == &other) {
        return *this;
    }

    _size = other._size;
    _data = other._data;

    return *this;
}

template<typename T>
TriangleMatrix<T> TriangleMatrix<T>::
operator+(const TriangleMatrix<T>& other) const {
    if (_size != other._size) {
        throw std::invalid_argument("TriangleMatrix: Incompatible sizes");
    }

    TriangleMatrix<T> result(_size);

    for (size_t i = 0; i < _size; i++) {
        result._data[i] = _data[i] + other._data[i];
    }

    return result;
}

template<typename T>
TriangleMatrix<T> TriangleMatrix<T>::
operator-(const TriangleMatrix<T>& other) const {
    if (_size != other._size) {
        throw std::invalid_argument("TriangleMatrix: Incompatible sizes");
    }

    TriangleMatrix<T> result(_size);

    for (size_t i = 0; i < _size; i++) {
        result._data[i] = _data[i] - other._data[i];
    }

    return result;
}

template<typename T>
TriangleMatrix<T> TriangleMatrix<T>::
operator*(const TriangleMatrix<T>& other) const {
    if (_size != other._size) {
        throw std::invalid_argument("TriangleMatrix: Incompatible sizes");
    }

    TriangleMatrix<T> result(_size);

    int terms_number = 1;

    for (size_t i = 0; i < _size; i++) {
        for (size_t j = 0; j < _size; j++) {
            if (i + j >= _size)
                continue;

            T sum = T();

            for (size_t k = 0; k < terms_number; k++) {
                sum += _data[j][k] * other._data[k + j][i - k];
            }

            result._data[j][i] = sum;
        }

        terms_number++;
    }

    return result;
}

template<typename T>
TriangleMatrix<T>& TriangleMatrix<T>::
operator+=(const TriangleMatrix<T>& other) {
    *this = *this + other;
    return *this;
}

template<typename T>
TriangleMatrix<T>& TriangleMatrix<T>::
operator-=(const TriangleMatrix<T>& other) {
    *this = *this - other;
    return *this;
}

template<typename T>
TriangleMatrix<T>& TriangleMatrix<T>::
operator*=(const TriangleMatrix<T>& other) {
    *this = *this * other;
    return *this;
}

#endif  // LIBS_LIB_TRIANGLE_MATRIX_TRIANGLE_MATRIX_H_
