#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class Time {
private:
    int totalSeconds;

public:
    explicit Time(int seconds = 0) : totalSeconds(seconds) {
        if (seconds < 0) throw std::invalid_argument("Time cannot be negative.");
    }

    Time& operator++() { // prefix
        ++totalSeconds;
        return *this;
    }

    Time operator++(int) { // postfix
        Time old = *this;
        ++totalSeconds;
        return old;
    }

    bool operator==(const Time& other) const {
        return totalSeconds == other.totalSeconds;
    }

    bool operator<(const Time& other) const {
        return totalSeconds < other.totalSeconds;
    }

    int seconds() const { return totalSeconds; }

    friend std::ostream& operator<<(std::ostream& out, const Time& t) {
        int value = t.totalSeconds;
        const int hours = value / 3600;
        value %= 3600;
        const int minutes = value / 60;
        const int seconds = value % 60;
        return out << hours << ':' << (minutes < 10 ? "0" : "") << minutes
                   << ':' << (seconds < 10 ? "0" : "") << seconds;
    }
};

class Playlist {
private:
    std::vector<std::string> tracks;

public:
    void add(const std::string& track) { tracks.push_back(track); }

    std::string& operator[](int index) {
        if (index < 0 || index >= static_cast<int>(tracks.size())) {
            throw std::out_of_range("Playlist index out of range.");
        }
        return tracks[static_cast<std::size_t>(index)];
    }

    const std::string& operator[](int index) const {
        if (index < 0 || index >= static_cast<int>(tracks.size())) {
            throw std::out_of_range("Playlist index out of range.");
        }
        return tracks[static_cast<std::size_t>(index)];
    }

    std::size_t size() const { return tracks.size(); }
};

int main() {
    Time t(5);
    Time a = t++;
    Time b = ++t;
    std::cout << "Postfix result, prefix result, final time: "
              << a << " | " << b << " | " << t << '\n';

    Playlist playlist;
    playlist.add("Track One");
    playlist.add("Track Two");
    std::cout << "Playing: " << playlist[0] << '\n';
    try {
        std::cout << playlist[-1] << '\n';
    } catch (const std::out_of_range& ex) {
        std::cout << "Checked access: " << ex.what() << '\n';
    }

    Time rollover(3599);
    ++rollover;
    std::cout << "Rollover: " << rollover << '\n';
    return 0;
}
