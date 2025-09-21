// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_MVECTOR_MVECTOR_H_
#define LIBS_LIB_MVECTOR_MVECTOR_H_

#include "libs/lib_tvector/tvector.h"

template<typename T>
class MVector {
 private:
    TVector<T> _data;

 public:
    MVector();
    explicit MVector(size_t);
    MVector(const MVector&);

    MVector<T>& operator=(const MVector<T>&);
    MVector operator+(const MVector<T>&);
    MVector operator-(const MVector<T>&);
    T operator*(const MVector<T>&);
    MVector operator*(T scalar);

    size_t size() const;
};

template<typename T>
MVector<T>::MVector() :_data() {}

template<typename T>
MVector<T>::MVector(size_t size) : _data(size) {
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
size_t MVector<T>::size() const {
    return _data.size();
}

#endif  // LIBS_LIB_MVECTOR_MVECTOR_H_
