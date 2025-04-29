#include "../lib.hpp"

int main() {
    const regex maskrex("mask = (.*)");
    const regex memrex("mem\\[(\\d+)\\] = (.*)");
    uint64_t vals = 0;
    vector<int> bits;
    unordered_map<uint64_t, uint64_t> memory;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, maskrex) && linematch.size() == 2) {
            string mask = linematch[1].str();
            bits.clear();
            vals = 0;
            int i = 0;
            for (char c : mask) {
                i++;
                vals <<= 1;
                if (c == 'X')
                    bits.push_back(mask.size() - i);
                else if (c == '1')
                    vals |= 1;
            }
        }
        else if (regex_match(s, linematch, memrex) && linematch.size() == 3) {
            uint64_t addr = stoul(linematch[1].str()) | vals;
            uint64_t val = stoul(linematch[2].str());
            uint64_t mask = -1;
            for (int j = 0; j < bits.size(); j++)
                mask &= ~(1lu << bits[j]);
            for (int i = 0; i < (1lu << bits.size()); i++) {
                uint64_t v = 0;
                for (int j = 0; j < bits.size(); j++)
                    v |= (((i >> j) & 1lu) << bits[j]);
                memory[(addr & mask) | v] = val;
            }
        }
    }

    uint64_t result = 0;
    for (auto &p : memory)
        result += p.second;
    cout << result << endl;

    return 0;
}

