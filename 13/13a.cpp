#include "../lib.hpp"

int main() {
    int t;
    cin >> t;
    string s;
    getline(cin, s);
    getline(cin, s);
    vector<string> bus = split_s(s, ",");

    int mn = t, mb = 0;
    for (string s : bus) {
        if (s != "x") {
            int b = stoi(s);
            int d = ((t - 1) / b + 1) * b - t;
            if (mn > d) {
                mn = d;
                mb = b;
            }
        }
    }
    cout << mb * mn << endl;
    return 0;
}

