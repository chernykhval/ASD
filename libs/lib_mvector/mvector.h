// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_MVECTOR_MVECTOR_H_
#define LIBS_LIB_MVECTOR_MVECTOR_H_

#include <cmath>
#include "libs/lib_tvector/tvector.h"

template<typename T>
class MVector {
 private:
    TVector<T> _data;

 public:
    MVector();
    explicit MVector(int);
    MVector(std::initializer_list<T> init);
    MVector(const MVector&);

    MVector<T>& operator=(const MVector<T>&);
    MVector<T> operator+(const MVector<T>&) const;
    MVector<T> operator-(const MVector<T>&) const;
    T operator*(const MVector<T>&) const;
    MVector<T> operator*(T scalar) const;
    MVector<T> operator/(T scalar) const;
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    MVector<T>& operator+=(const MVector<T>&);
    MVector<T>& operator-=(const MVector<T>&);
    MVector<T>& operator*=(T scalar);
    MVector<T>& operator/=(T scalar);

    T length() const;
    MVector<T> normalized() const;

    size_t size() const;
};

template<typename T>
MVector<T>::MVector() :_data() {}

template<typename T>
MVector<T>::MVector(int size) {
    if (size < 0) {
        throw std::invalid_argument("MVector: size must be non-negative");
    }
    _data = TVector<T>(size);
    _data.shrink_to_fit();
}

template<typename T>
MVector<T>::MVector(std::initializer_list<T> init) : _data(init) {
    _data.shrink_to_fit();
}

template<typename T>
MVector<T>::MVector(const MVector& other) {
    _data = other._data;
}

template<typename T>
MVector<T>& MVector<T>::operator=(const MVector<T>& other) {
    _data = other._data;
    return *this;
}

template<typename T>
MVector<T> MVector<T>::operator+(const MVector<T>& other) const {
    if (_data.size() != other._data.size()) {
        throw std::invalid_argument("MVector: size mismatch");
    }

    MVector<T> result(size());

    for (size_t i = 0; i < size(); i++) {
        result[i] = _data[i] + other._data[i];
    }

    return result;
}

template<typename T>
MVector<T> MVector<T>::operator-(const MVector<T>& other) const {
    if (_data.size() != other._data.size()) {
        throw std::invalid_argument("MVector: size mismatch");
    }

    MVector<T> result(size());

    for (size_t i = 0; i < size(); i++) {
        result[i] = _data[i] - other._data[i];
    }

    return result;
}

template<typename T>
T MVector<T>::operator*(const MVector<T>& other) const {
    if (_data.size() != other._data.size()) {
        throw std::invalid_argument("MVector: size mismatch");
    }

    T result{};

    for (size_t i = 0; i < size(); i++) {
        result = result + _data[i] * other._data[i];
    }

    return result;
}

template<typename T>
MVector<T> MVector<T>::operator*(T scalar) const  {
    MVector<T> result(size());

    for (size_t i = 0; i < size(); i++) {
        result[i] = _data[i] * scalar;
    }

    return result;
}

template<typename T>
MVector<T> MVector<T>::operator/(T scalar) const {
    if (scalar == T()) {
        throw std::invalid_argument("MVector: divide by zero");
    }

    MVector<T> result(size());

    for (size_t i = 0; i < size(); i++) {
        result[i] = _data[i] / scalar;
    }

    return result;
}

template<typename T>
T& MVector<T>::operator[](size_t index) {
    return _data[index];
}

template<typename T>
const T& MVector<T>::operator[](size_t index) const {
    return _data[index];
}

template<typename T>
MVector<T>& MVector<T>::operator+=(const MVector<T>& other) {
    *this = *this + other;

    return *this;
}

template<typename T>
MVector<T> & MVector<T>::operator-=(const MVector<T>& other) {
    *this = *this - other;

    return *this;
}

template<typename T>
MVector<T> & MVector<T>::operator*=(T scalar) {
    *this = *this * scalar;

    return *this;
}

template<typename T>
T MVector<T>::length() const {
    return sqrt(*this * *this);
}

template<typename T>
MVector<T> MVector<T>::normalized() const {
    T len = length();

    if (len == 0) {
        throw std::domain_error("Cannot normalize zero vector");
    }

    return *this / len;
}

template<typename T>
size_t MVector<T>::size() const {
    return _data.size();
}

#endif  // LIBS_LIB_MVECTOR_MVECTOR_H_
