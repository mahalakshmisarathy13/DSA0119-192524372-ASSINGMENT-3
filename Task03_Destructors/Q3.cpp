#include <iostream>
#include <stdexcept>
#include <string>

class Event {
private:
    std::string name;
    int rows;
    int seatsPerRow;
    bool** seats;
    int booked;

    void release() noexcept {
        if (seats != nullptr) {
            for (int r = 0; r < rows; ++r) {
                delete[] seats[r];
            }
            delete[] seats;
            seats = nullptr;
        }
    }

public:
    Event(const std::string& eventName, int rowCount, int seatsCount)
        : name(eventName), rows(rowCount), seatsPerRow(seatsCount),
          seats(nullptr), booked(0) {
        if (rows < 0 || seatsPerRow < 0) {
            throw std::invalid_argument("Rows and seats per row must be non-negative.");
        }

        if (rows == 0) {
            std::cout << "[constructor] " << name << ": zero-row event\n";
            return;
        }

        seats = new bool*[rows]();
        try {
            for (int r = 0; r < rows; ++r) {
                seats[r] = new bool[seatsPerRow]();
            }
        } catch (...) {
            for (int r = 0; r < rows; ++r) {
                delete[] seats[r];
            }
            delete[] seats;
            seats = nullptr;
            throw;
        }
        std::cout << "[constructor] " << name << ": seat map created\n";
    }

    // Avoid accidental shallow copies of the owned pointer structure.
    Event(const Event&) = delete;
    Event& operator=(const Event&) = delete;

    ~Event() {
        std::cout << "[destructor] " << name << ": " << booked
                  << " seat(s) still booked; releasing seat map\n";
        release();
    }

    void book(int row, int seat) {
        if (row < 0 || row >= rows || seat < 0 || seat >= seatsPerRow) {
            throw std::out_of_range("Seat position is invalid.");
        }
        if (!seats[row][seat]) {
            seats[row][seat] = true;
            ++booked;
            std::cout << "Booked row " << row << ", seat " << seat << '\n';
        }
    }

    void cancel(int row, int seat) {
        if (row < 0 || row >= rows || seat < 0 || seat >= seatsPerRow) {
            throw std::out_of_range("Seat position is invalid.");
        }
        if (seats[row][seat]) {
            seats[row][seat] = false;
            --booked;
            std::cout << "Cancelled row " << row << ", seat " << seat << '\n';
        }
    }
};

int main() {
    std::cout << "Stack event:\n";
    Event morning("Morning Show", 2, 3);
    morning.book(0, 1);
    morning.cancel(0, 1);

    std::cout << "\nBlock-scope event:\n";
    {
        Event workshop("Workshop", 1, 2);
        workshop.book(0, 0);
    } // workshop destructor runs here

    std::cout << "\nHeap event:\n";
    Event* evening = new Event("Evening Show", 2, 2);
    evening->book(1, 1);
    delete evening; // destructor runs here

    std::cout << "\nZero-row event:\n";
    Event empty("No-seat Event", 0, 10);
    return 0;
}
