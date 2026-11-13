#include <cstring>
#include <iostream>
#include <stdexcept>

class Text {
private:
    char* data;

public:
    explicit Text(const char* value = "") {
        if (value == nullptr) value = "";
        const std::size_t length = std::strlen(value);
        data = new char[length + 1];
        std::memcpy(data, value, length + 1);
    }

    Text(const Text& other) {
        const std::size_t length = std::strlen(other.data);
        data = new char[length + 1];
        std::memcpy(data, other.data, length + 1);
    }

    Text& operator=(const Text& other) {
        if (this == &other) return *this;
        const std::size_t length = std::strlen(other.data);
        char* replacement = new char[length + 1];
        std::memcpy(replacement, other.data, length + 1);
        delete[] data;
        data = replacement;
        return *this;
    }

    ~Text() { delete[] data; }

    Text& operator+=(const Text& other) {
        const std::size_t left = std::strlen(data);
        const std::size_t right = std::strlen(other.data);
        char* combined = new char[left + right + 1];
        std::memcpy(combined, data, left);
        std::memcpy(combined + left, other.data, right + 1);
        delete[] data;
        data = combined;
        return *this;
    }

    friend Text operator+(const Text& lhs, const Text& rhs) {
        Text result(lhs);
        result += rhs;
        return result;
    }

    bool operator==(const Text& other) const {
        return std::strcmp(data, other.data) == 0;
    }

    bool operator!=(const Text& other) const { return !(*this == other); }

    friend std::ostream& operator<<(std::ostream& out, const Text& value) {
        return out << value.data;
    }
};

int main() {
    Text first("Hello ");
    Text second("from ");
    Text third("C++!");
    Text message = first + second + third;
    std::cout << "Combined: " << message << '\n';

    Text copy = message;
    copy = copy; // self-assignment test
    std::cout << "Independent copy: " << copy << '\n';
    std::cout << std::boolalpha
              << "Equal: " << (message == copy)
              << ", Not equal: " << (first != second) << '\n';

    Text empty;
    std::cout << "Empty text between brackets: [" << empty << "]\n";
    return 0;
}
