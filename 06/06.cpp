#include "../lib.hpp"

int main() {
    smatch linematch;
    vector<map<char, int>> pass;
    vector<int> sz;
    pass.push_back(map<char, int>());
    sz.push_back(0);

    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        if (!s.size()) {
            pass.push_back(map<char, int>());
            sz.push_back(0);
            continue;
        }
        else
            sz.back()++;

        for (char c : s)
            pass.back()[c]++;
    }

    int result = 0, result2 = 0;
    int i = 0;
    for (auto &p : pass) {
        result += p.size();
        for (auto &c : p)
            if (c.second == sz[i])
                result2++;
        i++;
    }
    cout << result <<  ' ' << result2 << endl;

    return 0;
}

