// INTENTIONALLY UNSAFE EXPERIMENT. Do not use this as the final solution.
// The compiler-generated copy constructor copies only the pointer. Both objects
// then attempt delete[] on the same allocation, causing undefined behaviour.
#include <string>

class ShallowPrescription {
public:
    int n;
    std::string* medicines;

    explicit ShallowPrescription(int count)
        : n(count), medicines(new std::string[count]) {}
    ~ShallowPrescription() { delete[] medicines; }
    // No copy constructor: compiler-generated copy is shallow.
};

int main() {
    ShallowPrescription original(2);
    original.medicines[0] = "Paracetamol";
    ShallowPrescription copy = original; // shared pointer: double-delete risk
    copy.medicines[1] = "ORS";
}
