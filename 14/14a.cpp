#include "../lib.hpp"

int main() {
    const regex maskrex("mask = (.*)");
    const regex memrex("mem\\[(\\d+)\\] = (.*)");
    uint64_t bits = 0, vals = 0;
    unordered_map<uint64_t, uint64_t> memory;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, maskrex) && linematch.size() == 2) {
            string mask = linematch[1].str();
            bits = 0;
            vals = 0;
            for (char c : mask) {
                bits <<= 1;
                vals <<= 1;
                if (c == 'X')
                    bits |= 1;
                else if (c == '1')
                    vals |= 1;
            }
        }
        else if (regex_match(s, linematch, memrex) && linematch.size() == 3) {
            uint64_t addr = stoul(linematch[1].str());
            uint64_t val = stoul(linematch[2].str());
            memory[addr] = (val & bits) | vals;
        }
    }

    uint64_t result = 0;
    for (auto &p : memory)
        result += p.second;
    cout << result << endl;

    return 0;
}

