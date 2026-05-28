#include <string>
class Complex{
public:
    double Re;
    double Im;

    Complex();
    Complex(double re, double im);

    Complex operator+(const Complex& c) const;
    Complex operator-(const Complex& c) const;
    Complex operator*(const Complex& c) const;
    Complex operator/(const Complex& c) const;

    Complex& operator+=(const Complex& c);
    Complex& operator-=(const Complex& c);
    Complex& operator*=(const Complex& c);
    Complex& operator/=(const Complex& c);

    Complex operator-() const;

    bool operator==(const Complex& c) const;
    bool operator!=(const Complex& c) const;

    std::string toString() const;

};