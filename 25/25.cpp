#include "../lib.hpp"

int main() {
    uint64_t card = 14012298, door = 74241;
    //uint64_t card = 5764801, door = 17807724;
    long cloop = -1, dloop = -1;

    uint64_t val = 1;
    for (int i = 1; i < 200000000 && (cloop < 0 || dloop < 0); i++) {
        val = val * 7 % 20201227;
        if (val == card)
            cloop = i;
        if (val == door)
            dloop = i;
    }

    long ival = 1, jval = 1;
    for (int t = 0; t < cloop; t++)
        ival = ival * door % 20201227;
    for (int t = 0; t < dloop; t++)
        jval = jval * card % 20201227;
    cout << ival << ' ' << jval << endl;

    return 0;
}

