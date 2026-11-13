#include <iostream>
#include <stdexcept>
#include <string>

class Book {
private:
    std::string title;
    std::string author;
    int copies;

    static int validateCopies(int count) {
        if (count < 0) {
            throw std::invalid_argument("Number of copies cannot be negative.");
        }
        return count;
    }

public:
    // Empty record; later filled with setDetails().
    Book() : Book("", "", 0) {}

    // Donated book with title only.
    explicit Book(const std::string& bookTitle) : Book(bookTitle, "Unknown", 0) {}

    // Book with title, author and copy count.
    Book(const std::string& bookTitle, const std::string& bookAuthor, int count)
        : title(bookTitle), author(bookAuthor), copies(validateCopies(count)) {}

    // Convenient overload for title and copy count.
    Book(const std::string& bookTitle, int count)
        : Book(bookTitle, "Unknown", count) {}

    void setDetails(const std::string& bookTitle,
                    const std::string& bookAuthor, int count) {
        title = bookTitle;
        author = bookAuthor;
        copies = validateCopies(count);
    }

    void print() const {
        std::cout << "Title: " << (title.empty() ? "[empty]" : title)
                  << ", Author: " << author
                  << ", Copies: " << copies << '\n';
    }
};

// Deliberately incorrect initializer-list order for -Wreorder demonstration.
// Declaration order is title, then copies; list order below is reversed.
struct ReorderDemo {
    std::string title;
    int copies;
    ReorderDemo() : copies(3), title("Reorder demonstration") {}
};

int main() {
    try {
        Book empty;
        Book donated("C++ Fundamentals");
        Book complete("Object-Oriented Programming", "B. Stroustrup", 5);
        Book twoArguments("Data Structures", 4);

        std::cout << "Constructed Book objects:\n";
        empty.print();
        donated.print();
        complete.print();
        twoArguments.print();

        empty.setDetails("Computer Networks", "A. Tanenbaum", 2);
        std::cout << "\nAfter filling the empty record:\n";
        empty.print();

        std::cout << "\nNegative-copy test:\n";
        try {
            Book invalid("Invalid Book", "Unknown", -2);
            invalid.print();
        } catch (const std::invalid_argument& ex) {
            std::cout << "Rejected: " << ex.what() << '\n';
        }

        ReorderDemo demo;
        std::cout << "\n" << demo.title << ", copies = " << demo.copies << '\n';
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }
    return 0;
}
