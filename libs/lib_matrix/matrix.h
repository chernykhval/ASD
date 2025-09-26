// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_MATRIX_MATRIX_H_
#define LIBS_LIB_MATRIX_MATRIX_H_

// #include <sstream>
// #include <string>
// #include <iomanip>
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

    Matrix<T> operator+(const Matrix<T>&) const;
    Matrix<T> operator-(const Matrix<T>&) const;
    Matrix<T> operator*(const Matrix<T>&) const;

    Matrix<T>& operator+=(const Matrix<T>&);
    Matrix<T>& operator-=(const Matrix<T>&);
    Matrix<T>& operator*=(const Matrix<T>&);

    Matrix<T> operator*(const T&) const;
    Matrix<T> operator/(const T&) const;
    Matrix<T>& operator*=(const T&);
    Matrix<T>& operator/=(const T&);

    MVector<T> operator*(const MVector<T>&) const;

    Matrix<T>& operator=(const Matrix<T>&);

    bool operator==(const Matrix<T>& other) const;
    bool operator!=(const Matrix<T>& other) const;

    Matrix<T> transpose() const;
};

template<typename T>
Matrix<T>::Matrix() : _rows(0), _cols(0), _data() {}

template<typename T>
Matrix<T>::Matrix(size_t rows, size_t cols) : _rows(rows), _cols(cols) {
    _data = MVector<MVector<T>>(rows);

    for (size_t i = 0; i < rows; i++) {
        _data[i] = MVector<T>(cols);
    }
}

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

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const {
    if (_rows != other._rows || _cols != other._cols) {
        throw std::invalid_argument("Matrix: Incompatible sizes");
    }

    Matrix<T> result(_rows, _cols);

    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            result._data[i] = _data[i] + other._data[i];
        }
    }

    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const {
    if (_rows != other._rows || _cols != other._cols) {
        throw std::invalid_argument("Matrix: Incompatible sizes");
    }

    Matrix<T> result(_rows, _cols);

    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            result._data[i] = _data[i] - other._data[i];
        }
    }

    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const {
    if (_cols != other._rows) {
        throw std::invalid_argument("Matrix: Incompatible sizes");
    }

    Matrix<T> result(_rows, other._cols);
    Matrix<T> other_transpose = other.transpose();

    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < other._cols; j++) {
            result._data[i][j] = _data[i] * other_transpose._data[j];
        }
    }

    return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other) {
    *this = *this + other;
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other) {
    *this = *this - other;
    return *this;
}

template<typename T>
Matrix<T> & Matrix<T>::operator*=(const Matrix<T>& other) {
    *this = *this * other;
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const T& scalar) const {
    Matrix<T> result(_rows, _cols);

    for (size_t i = 0; i < _rows; i++) {
        result._data[i] = _data[i] * scalar;
    }

    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator/(const T& scalar) const {
    Matrix<T> result(_rows, _cols);

    for (size_t i = 0; i < _rows; i++) {
        result._data[i] = _data[i] / scalar;
    }

    return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(const T& scalar) {
    *this = *this * scalar;
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator/=(const T& scalar) {
    *this = *this / scalar;
    return *this;
}

template<typename T>
MVector<T> Matrix<T>::operator*(const MVector<T>& column) const {
    MVector<T> result(_rows);

    for (size_t i = 0; i < _rows; i++) {
        result[i] = _data[i] * column;
    }

    return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
    if (this == &other) {
        return *this;
    }

    _cols = other._cols;
    _rows = other._rows;
    _data = other._data;

    return *this;
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T>& other) const {
    for (size_t i = 0; i < _rows; i++) {
        if (_data[i] != other._data[i]) {
            return false;
        }
    }

    return true;
}

template<typename T>
bool Matrix<T>::operator!=(const Matrix<T> &other) const {
    return !(*this == other);
}

template<typename T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix<T> result(_cols, _rows);

    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            result._data[j][i] = _data[i][j];
        }
    }

    return result;
}

// template<typename T>
// size_t Matrix<T>::get_element_display_width(const T& element) {
//     std::stringstream ss;
//     ss << element;
//
//     return ss.str().length();
// }
//
// template <typename T>
// std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
//     if (matrix.rows() == 0) {
//         return os;
//     }
//
//     size_t max_width = 2;
//
//     for (size_t i = 0; i < matrix.rows(); i++) {
//         for (size_t j = 0; j < matrix.cols(); j++) {
//             size_t current_width = get_element_width(matrix[i][j]);
//             if (current_width > max_width) {
//                 max_width = current_width;
//             }
//         }
//     }
//
//     for (size_t i = 0; i < matrix.rows(); ++i) {
//         os << "| ";
//
//         for (size_t j = 0; j < matrix.cols(); ++j) {
//             os << std::setw(static_cast<int>(max_width))
//             << matrix[i][j] << " ";
//         }
//
//         os << "|\n";
//     }
//
//     return os;
// }
//
// template <typename T>
// std::istream& operator>>(std::istream& is, Matrix<T>& matrix) {
//
//     return is;
// }

#endif  // LIBS_LIB_MATRIX_MATRIX_H_
