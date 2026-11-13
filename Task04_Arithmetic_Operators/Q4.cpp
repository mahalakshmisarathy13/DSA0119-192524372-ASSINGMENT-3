#include <iomanip>
#include <iostream>

class Money {
private:
    long long paise;

public:
    Money(long long rupees = 0, int p = 0)
        : paise(rupees * 100 + p) {}

    Money operator+(const Money& other) const {
        return Money(0, static_cast<int>(paise + other.paise));
    }

    Money operator-(const Money& other) const {
        return Money(0, static_cast<int>(paise - other.paise));
    }

    Money& operator+=(const Money& other) {
        paise += other.paise;
        return *this;
    }

    bool operator==(const Money& other) const {
        return paise == other.paise;
    }

    bool operator<(const Money& other) const {
        return paise < other.paise;
    }

    friend std::ostream& operator<<(std::ostream& out, const Money& amount) {
        const long long absolute = amount.paise < 0 ? -amount.paise : amount.paise;
        if (amount.paise < 0) out << "-";
        out << "Rs " << absolute / 100 << '.'
            << std::setw(2) << std::setfill('0') << absolute % 100
            << std::setfill(' ');
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Money& amount) {
        long long rupees;
        int p;
        if (in >> rupees >> p) {
            amount.paise = rupees * 100 + p;
        }
        return in;
    }
};

int main() {
    Money a(120, 75), b(79, 25);
    Money c = a + b;
    std::cout << c << '\n' << std::boolalpha << (c == Money(200)) << '\n';

    Money x(0, 75), y(0, 50);
    std::cout << "Carry test: " << x + y << '\n';

    Money negative = Money(1, 0) - Money(2, 25);
    std::cout << "Negative subtraction: " << negative << '\n';

    x += y;
    std::cout << "After +=: " << x << '\n';
    return 0;
}
