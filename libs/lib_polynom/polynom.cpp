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

bool Monom::is_zero() const {
    return _coeff == 0;
}

bool Monom::equal(const Monom& other) const {
    return *this == other && _coeff == other._coeff;
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

Polynom::Polynom(const std::string& name) : _name(name), _monomes() {
}

Polynom::Polynom(const Polynom& polynom) : _name(polynom._name),
_monomes(polynom._monomes) {
}

Polynom& Polynom::operator+=(const Monom& monom) {
    if (monom.is_zero()){
        return *this;
    }

    if(_monomes.is_empty() || monom > *(_monomes.begin())){
        _monomes.push_front(monom);

        return *this;
    }

    for (auto it = _monomes.begin(); it != _monomes.end(); ++it) {
        if (*it == monom) {
            *it += monom;

            if (it->is_zero()){
                _monomes.erase(it);
            }

            return *this;
        }

        auto next = it;
        ++next;

        if (next == _monomes.end() || monom > *next){
            _monomes.insert(it, monom);

            return *this;
        }
    }

    _monomes.push_back(monom);

    return *this;
}

Polynom& Polynom::operator-=(const Monom& monom) {
    *this += (-monom);
    return *this;
}

Polynom& Polynom::operator*=(const Monom& monom) {
    if (monom.is_zero()) {
        _monomes.clear();
        return *this;
    }

    for (auto& m : _monomes) {
        m *= monom;
    }

    return *this;
}

Polynom Polynom::operator*(double value) const {
    Polynom result(*this);

    result *= value;
    return result;
}

Polynom Polynom::operator/(double value) const {
    Polynom result(*this);

    result /= value;
    return result;
}

bool Polynom::operator==(const Polynom& other) const {
    if (_monomes.size() != other._monomes.size()) {
        return false;
    }

    auto it1 = _monomes.begin();
    auto it2 = other._monomes.begin();

    while (it1 != _monomes.end()) {
        if (!it1->equal(*it2)) {
            return false;
        }

        ++it1;
        ++it2;
    }

    return true;
}

bool Polynom::operator!=(const Polynom& other) const {
    return !(*this == other);
}

Polynom Polynom::operator-() const {
    Polynom result(*this);

    return result * (-1.0);
}

Polynom& Polynom::operator*=(double value) {
    if (value == 0.0) {
        _monomes.clear();
        return *this;
    }

    for (auto& monom : _monomes) {
        monom *= value;
    }

    return *this;
}

Polynom& Polynom::operator/=(double value) {
    if (value == 0.0) {
        throw std::invalid_argument("Polynom: division by zero");
    }

    for (auto& monom : _monomes) {
        monom /= value;
    }

    return *this;
}

double Polynom::calculate(double x, double y, double z) const {
    double result = 0.0;

    for (auto& monom : _monomes) {
        result += monom.calculate(x, y, z);
    }

    return  result;
}

Polynom& Polynom::operator=(const Polynom& polynom) {
    if (this == &polynom) {
        return *this;
    }

    _name = polynom._name;
    _monomes = polynom._monomes;

    return *this;
}

size_t Polynom::size() const {
    return _monomes.size();
}

std::string Polynom::name() const {
    return _name;
}

void Polynom::add_monom(const Monom& monom) {

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

std::ostream& operator<<(std::ostream& os, const Polynom& p) {
    for (auto it = p._monomes.begin(); it != p._monomes.end(); ++it) {
        if (it != p._monomes.begin())
            os << " + ";
        os << *it;
    }

    return os;
}
