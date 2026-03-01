// Copyright 2026 Chernykh Valentin

#ifndef LIBS_LIB_POLYNOM_POLYNOM_H_
#define LIBS_LIB_POLYNOM_POLYNOM_H_

#include <cstddef>
#include <iosfwd>
#include <string>

#include "libs/lib_list/list.h"

class Monom {
 private:
    static constexpr size_t VAR_COUNT = 3;
    double _coeff;
    int _powers[VAR_COUNT];

 public:
    explicit Monom(double coeff = 0.0, const int* powers = nullptr);
    Monom(const Monom& monom);

    bool operator==(const Monom& monom) const;
    bool operator!=(const Monom& monom) const;
    bool operator>(const Monom& monom) const;
    bool operator<(const Monom& monom) const;

    Monom operator+(const Monom& monom) const;
    Monom operator-(const Monom& monom) const;
    Monom operator*(const Monom& monom) const;
    Monom operator/(const Monom& monom) const;

    Monom operator*(double value) const;
    Monom operator/(double value) const;
    Monom operator-() const;

    Monom& operator+=(const Monom& monom);
    Monom& operator-=(const Monom& monom);
    Monom& operator*=(const Monom& monom);
    Monom& operator/=(const Monom& monom);

    Monom& operator*=(double value);
    Monom& operator/=(double value);

    double calculate(double x, double y, double z) const;

    friend std::ostream& operator<<(std::ostream& os, const Monom& monom);
    friend std::istream& operator>>(std::istream& is, Monom& monom);

    Monom& operator=(const Monom& monom);
};

class Polynom {
 private:
    List<Monom> _monomes;
    std::string _name;

 public:
    explicit Polynom(const std::string& name = "");
    Polynom(const Polynom& polynom);

    Polynom operator+(const Polynom& polynom) const;
    Polynom operator-(const Polynom& polynom) const;
    Polynom operator*(const Polynom& polynom) const;
    Polynom& operator+=(const Polynom& polynom);
    Polynom& operator-=(const Polynom& polynom);
    Polynom& operator*=(const Polynom& polynom);

    Polynom operator*(double value) const;
    Polynom operator/(double value) const;
    Polynom operator-() const;

    Polynom& operator*=(double value);
    Polynom& operator/=(double value);

    bool operator==(const Polynom& other) const;
    bool operator!=(const Polynom& other) const;

    double calculate(double x, double y, double z) const;

    friend std::ostream& operator<<(std::ostream& os, const Polynom& p);
    friend std::istream& operator>>(std::istream& is, Polynom& p);

 private:
    void add_monom(const Monom& m);
};

#endif  // LIBS_LIB_POLYNOM_POLYNOM_H_
