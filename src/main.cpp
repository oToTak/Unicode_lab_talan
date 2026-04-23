
#include <iostream>

#include <fstream>

#include "methods.hpp"



int main(int argc, char* argv[]) {
    if (argc < 2) return 1;
    std::ifstream f(argv[1], std::ios::binary);
    if (!f.is_open()) return 3;
    std::vector<uint8_t> d((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    if (d.empty()) return 0;

    Stats s;
    if (d.size() >= 4 && d[0] == 0x00 && d[1] == 0x00 && d[2] == 0xFE && d[3] == 0xFF) {
        process_utf32(d, s, false);
    } else if (d.size() >= 4 && d[0] == 0xFF && d[1] == 0xFE && d[2] == 0x00 && d[3] == 0x00) {
        process_utf32(d, s, true);
    } else if (d.size() >= 3 && d[0] == 0xEF && d[1] == 0xBB && d[2] == 0xBF) {
        process_utf8(d, s);
    } else if (d.size() >= 2 && d[0] == 0xFE && d[1] == 0xFF) {
        process_utf16(d, s, false);
    } else if (d.size() >= 2 && d[0] == 0xFF && d[1] == 0xFE) {
        process_utf16(d, s, true);
    } else {
        process_utf8(d, s);
    }

    std::cout << "Units: " << s.units << "\nPoints: " << s.points << "\nWords: " << s.words << "\nErrors: " << s.errors << std::endl;
    return 0;

}

