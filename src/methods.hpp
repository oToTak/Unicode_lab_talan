#pragma once
#include <vector>
#include <cstdint>

struct Stats {
    size_t units = 0;
    size_t points = 0;
    size_t words = 0;
    size_t errors = 0;
};

bool is_ws(uint32_t u);
void process_utf8(const std::vector<uint8_t>& d, Stats& s);
void process_utf16(const std::vector<uint8_t>& d, Stats& s, bool le);
void process_utf32(const std::vector<uint8_t>& d, Stats& s, bool le);
