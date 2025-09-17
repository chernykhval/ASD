// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_MATRIX_MATRIX_H_
#define LIBS_LIB_MATRIX_MATRIX_H_

template<typename T>
class Matrix{
 private:
    int _m, _n;

 public:
    Matrix(int m, int n);

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(const T& scalar) const;

    Matrix transpose() const;
    double determinant() const;
};

template<typename T>
Matrix<T>::Matrix(const int m, const int n) : _m(m), _n(n) {}

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
    return Matrix(_m, _n);
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const T& scalar) const {
    return Matrix(_m, _n);
}

template<typename T>
Matrix<T> Matrix<T>::transpose() const {
    return Matrix(_m, _n);
}

#endif  // LIBS_LIB_MATRIX_MATRIX_H_
