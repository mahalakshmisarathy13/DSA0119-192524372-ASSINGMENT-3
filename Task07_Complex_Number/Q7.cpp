#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

class Complex {
private:
    double real;
    double imag;

public:
    Complex() : real(0.0), imag(0.0) {}
    Complex(double r) : real(r), imag(0.0) {}
    Complex(double r, double i) : real(r), imag(i) {}

    Complex operator+(const Complex& z) const {
        return Complex(real + z.real, imag + z.imag);
    }

    Complex operator-(const Complex& z) const {
        return Complex(real - z.real, imag - z.imag);
    }

    Complex operator*(const Complex& z) const {
        return Complex(real * z.real - imag * z.imag,
                       real * z.imag + imag * z.real);
    }

    Complex operator/(const Complex& z) const {
        const double denominator = z.real * z.real + z.imag * z.imag;
        if (denominator == 0.0) {
            throw std::domain_error("Cannot divide by zero impedance.");
        }
        return Complex((real * z.real + imag * z.imag) / denominator,
                       (imag * z.real - real * z.imag) / denominator);
    }

    bool operator==(const Complex& z) const {
        constexpr double eps = 1e-10;
        return std::abs(real - z.real) < eps &&
               std::abs(imag - z.imag) < eps;
    }

    double magnitude() const { return std::hypot(real, imag); }

    friend std::ostream& operator<<(std::ostream& out, const Complex& z) {
        out << std::fixed << std::setprecision(4)
            << z.real << (z.imag < 0 ? " - j" : " + j")
            << std::abs(z.imag);
        return out;
    }
};

int main() {
    try {
        const double R = 10.0;
        const double XL = 5.0;
        const double XC = 2.0;

        const Complex resistor(R, 0.0);
        const Complex inductor(0.0, XL);
        const Complex capacitor(0.0, -XC);

        const Complex series = resistor + inductor + capacitor;
        std::cout << "Series impedance: " << series
                  << "\nMagnitude: " << series.magnitude() << '\n';

        const Complex z1(10.0, 5.0);
        const Complex z2(20.0, -2.0);
        const Complex parallel = (z1 * z2) / (z1 + z2);
        std::cout << "\nParallel impedance: " << parallel
                  << "\nMagnitude: " << parallel.magnitude() << '\n';

        try {
            const Complex zero;
            const Complex invalid = z1 / zero;
            std::cout << invalid << '\n';
        } catch (const std::domain_error& ex) {
            std::cout << "\nZero-division test: " << ex.what() << '\n';
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }
    return 0;
}
