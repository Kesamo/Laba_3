#include <format>
#include "Complex.hpp"


Complex::Complex() : Re(0.0), Im(0.0) {}
Complex::Complex(double re, double im) : Re(re), Im(im) {}

Complex Complex::operator+(const Complex& c) const {
    return {Re + c.Re, Im + c.Im};
}

Complex Complex::operator-(const Complex& c) const {
    return {Re - c.Re, Im - c.Im};
}

Complex Complex::operator*(const Complex& c) const {
    return {Re * c.Re - Im * c.Im, Re * c.Im + Im * c.Re};
}

Complex Complex::operator/(const Complex& c) const {
    double denom = c.Re * c.Re + c.Im * c.Im;
    return {(Re * c.Re + Im * c.Im) / denom, (Im * c.Re - Re * c.Im) / denom};
}

Complex& Complex::operator+=(const Complex& c) {
    *this = *this + c;
    return *this;
}
Complex& Complex::operator-=(const Complex& c) {
    *this = *this - c;
    return *this;
}
Complex& Complex::operator*=(const Complex& c) {
    *this = *this * c;
    return *this;
}
Complex& Complex::operator/=(const Complex& c) {
    *this = *this / c;
    return *this;
}

Complex Complex::operator-() const {
    return {-Re, -Im};
}

bool Complex::operator==(const Complex& c) const {
    return Re == c.Re && Im == c.Im;
}

bool Complex::operator!=(const Complex& c) const {
    return !(*this == c);
}

std::string Complex::toString() const {
    return std::format("{}{}i", Re, Im);
}