
#include "methods.hpp"



bool is_ws(uint32_t u) {

    return (u == 0x20 || u == 0x09 || u == 0x0A || u == 0x0D);

}



void process_utf8(const std::vector<uint8_t>& d, Stats& s) {

    s.units = d.size();

    bool ws = true;

    size_t start = (d.size() >= 3 && d[0] == 0xEF && d[1] == 0xBB && d[2] == 0xBF) ? 3 : 0;

    for (size_t i = start; i < d.size(); ++i) {

        size_t step = 0;

        if ((d[i] & 0x80) == 0) {

            s.points++;

            if (is_ws(d[i])) ws = true;

            else if (ws) { s.words++; ws = false; }

            continue;

        } else if ((d[i] & 0xE0) == 0xC0) step = 1;

        else if ((d[i] & 0xF0) == 0xE0) step = 2;

        else if ((d[i] & 0xF8) == 0xF0) step = 3;

        else { s.errors++; continue; }

        bool valid = true;

        for (size_t j = 1; j <= step; ++j) {

            if (i + j >= d.size() || (d[i + j] & 0xC0) != 0x80) { valid = false; break; }

        }

        if (valid) {

            s.points++; i += step;

            if (ws) { s.words++; ws = false; }

        } else { s.errors++; }

    }

}



void process_utf16(const std::vector<uint8_t>& d, Stats& s, bool le) {

    s.units = d.size() / 2;

    bool ws = true;

    for (size_t i = 2; i + 1 < d.size(); i += 2) {

        uint16_t u = le ? (d[i] | (d[i+1] << 8)) : ((d[i] << 8) | d[i+1]);

        if (u >= 0xD800 && u <= 0xDBFF) {

            if (i + 3 < d.size()) {

                uint16_t u2 = le ? (d[i+2] | (d[i+3] << 8)) : ((d[i+2] << 8) | d[i+3]);

                if (u2 >= 0xDC00 && u2 <= 0xDFFF) { 

                    i += 2; s.points++; 

                    if (ws) { s.words++; ws = false; }

                } else s.errors++;

            } else s.errors++;

        } else {

            s.points++;

            if (is_ws(u)) ws = true;

            else if (ws) { s.words++; ws = false; }

        }

    }

}

