// Copyright 2026 Chernykh Valentin

#include <cmath>
#include <iostream>

#include "libs/lib_polynom/polynom.h"

Monom::Monom(double coeff, const int* powers) : _coeff(coeff) {
    if (powers == nullptr) {
        for (size_t i = 0; i < VAR_COUNT; ++i) {
            _powers[i] = 0;
        }
    } else {
        for (size_t i = 0; i < VAR_COUNT; ++i) {
            if (powers[i] < 0) {
                throw std::out_of_range("Error: powers cannot be negative");
            }

            _powers[i] = powers[i];
        }
    }
}

Monom::Monom(const Monom& monom) : _coeff(monom._coeff) {
    for (size_t i = 0; i < VAR_COUNT; ++i) {
        _powers[i] = monom._powers[i];
    }
}

bool Monom::operator==(const Monom& monom) const {
    for (size_t i = 0; i < VAR_COUNT; ++i) {
        if (_powers[i] != monom._powers[i]) {
            return false;
        }
    }

    return true;
}

bool Monom::operator!=(const Monom& monom) const {
    return !(*this == monom);
}

bool Monom::operator>(const Monom& monom) const {
    for (size_t i = 0; i < VAR_COUNT; ++i) {
        if (_powers[i] != monom._powers[i]) {
            return _powers[i] > monom._powers[i];
        }
    }

    return false;
}

bool Monom::operator<(const Monom& monom) const {
    return !(*this == monom || *this > monom);
}

Monom Monom::operator+(const Monom& monom) const {
    Monom result(*this);

    return result += monom;
}

Monom Monom::operator-(const Monom& monom) const {
    Monom result(*this);

    return result -= monom;
}

Monom Monom::operator*(const Monom& monom) const {
    Monom result(*this);

    return result *= monom;
}

Monom Monom::operator/(const Monom& monom) const {
    Monom result(*this);

    return result /= monom;
}

Monom Monom::operator*(double value) const {
    Monom result(*this);

    return result *= value;
}

Monom Monom::operator/(double value) const {
    Monom result(*this);

    return result /= value;
}

Monom Monom::operator-() const {
    Monom result(*this);
    result._coeff = -result._coeff;
    return result;
}

Monom& Monom::operator+=(const Monom& monom) {
    if (*this != monom) {
        throw std::invalid_argument("Error: monomes are not similar");
    }

    _coeff += monom._coeff;

    return *this;
}

Monom& Monom::operator-=(const Monom& monom) {
    return *this += (-monom);
}

Monom& Monom::operator*=(const Monom& monom) {
    _coeff *= monom._coeff;

    for (size_t i = 0; i < VAR_COUNT; ++i) {
        _powers[i] += monom._powers[i];
    }

    return *this;
}

Monom& Monom::operator/=(const Monom& monom) {
    if (monom._coeff == 0.0) {
        throw std::invalid_argument("Error: division by zero monom");
    }

    for (size_t i = 0; i < VAR_COUNT; ++i) {
        if (this->_powers[i] < monom._powers[i]) {
            throw std::out_of_range("Error: resulting power would be negative");
        }
    }

    _coeff /= monom._coeff;

    for (size_t i = 0; i < VAR_COUNT; ++i) {
        _powers[i] -= monom._powers[i];
    }

    return *this;
}

Monom& Monom::operator*=(double value) {
    _coeff *= value;

    return *this;
}

Monom& Monom::operator/=(double value) {
    if (value == 0.0) {
        throw std::invalid_argument("Error: division by zero");
    }

    _coeff /= value;

    return *this;
}

double Monom::calculate(double x, double y, double z) const {
    double result = _coeff
    * std::pow(x, _powers[0])
    * std::pow(y, _powers[1])
    * std::pow(z, _powers[2]);

    return result;
}

Monom& Monom::operator=(const Monom& monom) {
    if (this == &monom) {
        return *this;
    }

    _coeff = monom._coeff;

    for (size_t i = 0; i < VAR_COUNT; ++i) {
        _powers[i] = monom._powers[i];
    }

    return *this;
}

std::ostream& operator<<(std::ostream& os, const Monom& monom) {
    os << "(" << monom._coeff
    << " * x^" << monom._powers[0]
    << " * y^" << monom._powers[1]
    << " * z^" << monom._powers[2]
    << ")";

    return os;
}

std::istream& operator>>(std::istream& is, Monom& monom) {
    is >> monom._coeff
    >> monom._powers[0]
    >> monom._powers[1]
    >> monom._powers[2];

    return is;
}
