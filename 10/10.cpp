#include "../lib.hpp"

int main() {
    vector<int> jolt;
    while (cin) {
        int num;
        cin >> num;
        if (!cin) break;
        jolt.push_back(num);
    }

    jolt.push_back(0);
    sort(jolt.begin(), jolt.end());
    jolt.push_back(jolt.back() + 3);

    int d1 = 0, d3 = 0;
    for (int i = 1; i < jolt.size(); i++)
        if (jolt[i] - jolt[i-1] == 1)
            d1++;
        else if (jolt[i] - jolt[i-1] == 3)
            d3++;
    cout << d1 * d3 << endl;

    vector<uint64_t> ways(jolt.size(), 0);
    ways[0] = 1;
    for (int i = 1; i < jolt.size(); i++)
        for (int j = i - 3; j < i; j++)
            if (j >= 0 && (jolt[i] - jolt[j] <= 3))
                ways[i] += ways[j];
    cout << ways[jolt.size() - 1] << endl;

    return 0;
}

