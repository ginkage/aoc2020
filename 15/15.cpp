#include "../lib.hpp"

int main() {
    unordered_map<int, int> last;

    string s;
    getline(cin, s);
    vector<int> init = split_i(s, ",");

    for (int i = 0; i < init.size() - 1; i++)
        last[init[i]] = i;

    int prev = init.back();
    for (int t = init.size(); t < 30000000; t++) {
        auto it = last.find(prev);
        int next = (it == last.end()) ? 0 : t - 1 - it->second;
        last[prev] = t - 1;
        prev = next;
    }
    cout << prev << endl;

    return 0;
}

