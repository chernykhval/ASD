// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_MATRIX_MATRIX_H_
#define LIBS_LIB_MATRIX_MATRIX_H_

#include <iostream>

template<typename T>
class Matrix{
 private:
    size_t _m, _n;

 public:
    Matrix();
    Matrix(size_t m, size_t n);

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(const T& scalar) const;

    Matrix transpose() const;
    T determinant() const;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& matrix);

    template<typename U>
    friend std::istream& operator>>(std::istream& is, Matrix<U>& matrix);
};


template<typename T>
Matrix<T>::Matrix() : _m(0), _n(0) {}

template<typename T>
Matrix<T>::Matrix(const size_t m, const size_t n) : _m(m), _n(n) {}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& other) const {
    return Matrix(_m, _n);
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix& other) const {
    return Matrix(_m, _n);
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix& other) const {
    return Matrix(_m, other._n);
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const T& scalar) const {
    return Matrix(_m, _n);
}

template<typename T>
Matrix<T> Matrix<T>::transpose() const {
    return Matrix(_m, _n);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
    os << "operator<<: Matrix(" << matrix._m
    << ", " << matrix._n << ")" << std::endl;
    return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, Matrix<T>& matrix) {
    std::cout << "operator>>: Input matrix(" << matrix._m
    << ", " << matrix._n << ")" << std::endl;
    return is;
}

#endif  // LIBS_LIB_MATRIX_MATRIX_H_
