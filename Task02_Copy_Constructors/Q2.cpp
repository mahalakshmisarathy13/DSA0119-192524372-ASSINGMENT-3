#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

class Prescription {
private:
    int n;
    std::string* medicines;

public:
    explicit Prescription(int count)
        : n(count), medicines(count > 0 ? new std::string[count] : nullptr) {
        if (count < 0) {
            throw std::invalid_argument("Medicine count cannot be negative.");
        }
    }

    // Deep-copy constructor.
    Prescription(const Prescription& other)
        : n(other.n), medicines(n > 0 ? new std::string[n] : nullptr) {
        for (int i = 0; i < n; ++i) {
            medicines[i] = other.medicines[i];
        }
        std::cout << "[copy constructor] copied " << n << " medicine(s)\n";
    }

    // Deep-copy assignment with self-assignment protection and strong safety.
    Prescription& operator=(const Prescription& other) {
        if (this == &other) {
            return *this;
        }

        std::string* newMedicines =
            other.n > 0 ? new std::string[other.n] : nullptr;

        try {
            for (int i = 0; i < other.n; ++i) {
                newMedicines[i] = other.medicines[i];
            }
        } catch (...) {
            delete[] newMedicines;
            throw;
        }

        delete[] medicines;
        medicines = newMedicines;
        n = other.n;
        return *this;
    }

    ~Prescription() {
        delete[] medicines;
    }

    void set(int i, const std::string& medicine) {
        if (i < 0 || i >= n) {
            throw std::out_of_range("Medicine index out of range.");
        }
        medicines[i] = medicine;
    }

    std::string get(int i) const {
        if (i < 0 || i >= n) {
            throw std::out_of_range("Medicine index out of range.");
        }
        return medicines[i];
    }

    int size() const { return n; }
};

void inspectByValue(Prescription p) {
    std::cout << "Passed by value; size = " << p.size() << '\n';
}

void inspectByConstReference(const Prescription& p) {
    std::cout << "Passed by const reference; size = " << p.size() << '\n';
}

int main() {
    Prescription p(2);
    p.set(0, "Paracetamol");
    p.set(1, "ORS");

    Prescription q = p; // copy constructor
    q.set(1, "Cetirizine");

    Prescription r(1);
    r = p; // copy assignment

    p.set(0, "Ibuprofen");

    std::cout << p.get(0) << ' ' << p.get(1)
              << " | " << q.get(0) << ' ' << q.get(1)
              << " | " << r.get(0) << ' ' << r.get(1) << '\n';

    r = r; // self-assignment test
    inspectByValue(p);
    inspectByConstReference(p);
    return 0;
}
