#include "../lib.hpp"

/*
CRT:

Step 1: Identify the divisors and their corresponding remainders.
Step 2: Check if the divisors are pairwise coprime. If they are, proceed with CRT.
Step 3: Calculate the product of all divisors (let's call it M).
Step 4: For each divisor, calculate its corresponding "M_i" (M divided by that divisor).
Step 5: For each M_i, find the modular inverse of that M_i modulo the corresponding divisor (let's call it "n_i"). The modular inverse, n_i, is a number such that (M_i * n_i) is congruent to 1 modulo the divisor.
Step 6: Calculate the solution by summing the product of the remainder, M_i, and its modular inverse (n_i) for all divisors. The result is then taken modulo M.
*/

uint64_t modpow(__int128 base, uint64_t exp, uint64_t mod) {
    base %= mod;
    uint64_t result = 1;
    while (exp > 0) {
        if (exp & 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

uint64_t invmod(uint64_t base, uint64_t mod) {
    return modpow(base, mod - 2, mod);
}

int main() {
    string s;
    getline(cin, s);
    getline(cin, s);
    vector<string> bus = split_s(s, ",");

    // Step 1
    int n = 0;
    vector<int> period, remain;
    for (int i = 0; i < bus.size(); i++) {
        if (bus[i] != "x") {
            int per = stoi(bus[i]);
            int rem = i == 0 ? 0 : per - i;
            while (rem < 0)
                rem += per;
            period.push_back(per);
            remain.push_back(rem);
            n++;
        }
    }

    // Step 3
    uint64_t product = 1;
    for (int i = 0; i < n; i++)
        product *= period[i];

    // Step 4
    vector<uint64_t> mi;
    for (int i = 0; i < n; i++)
        mi.push_back(product / period[i]);

    // Step 5
    vector<uint64_t> ni;
    for (int i = 0; i < n; i++)
        ni.push_back(invmod(mi[i], period[i]));

    // Step 6
    uint64_t result = 0;
    for (int i = 0; i < n; i++)
        result = (result + remain[i] * mi[i] * ni[i]) % product;
    cout << result << endl;

    return 0;
}

