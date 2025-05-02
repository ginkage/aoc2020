#include "../lib.hpp"

typedef vector<int> match_t;
typedef vector<match_t> rule_t;
unordered_map<int, rule_t> rules;

bool check(string &s, int &i, int r) {
    bool result = false;
    if (i >= s.size())
        result = false;
    else if (r < 0) {
        if (s[i] == -r) {
            i++;
            result = true;
        }
        else
            result = false;
    }
    else
        for (match_t &m : rules[r]) {
            int pos = i;
            bool good = true;
            for (int t : m)
                if (!check(s, pos, t)) {
                    good = false;
                    break;
                }

            if (good && (r != 0 || pos == s.size())) {
                i = pos;
                result = true;
                break;
            }
        }

    return result;
}

int main() {
    const regex linerex("(.*): (.*)");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 3) {
            int from = stoi(linematch[1].str());
            for (string rs : split_s(linematch[2].str(), " | ")) {
                match_t m;
                for (string ss : split_s(rs, " ")) {
                    if (ss[0] == '"')
                        m.push_back(-ss[1]);
                    else
                        m.push_back(stoi(ss));
                }
                rules[from].push_back(m);
            }
        }
        else if (!s.size())
            break;
    }

    int result = 0, result2 = 0;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        int it = 0;
        if (check(s, it, 0))
            result++;

        if (s.size() % 8 == 0) {
            int a = 0, b = 0;
            bool good = true;
            for (int i = 0; i < s.size() / 8 && good; i++) {
                string ss = s.substr(i * 8, 8);
                it = 0;
                if (check(ss, it, 42)) {
                    a++;
                    if (b > 0)
                        good = false;
                }
                else {
                    it = 0;
                    if (check(ss, it, 31))
                        b++;
                    else
                        good = false;
                }
            }
            if (good && a > b && b > 0)
                result2++;
        }
    }
    cout << result << ' ' << result2 << endl;

    return 0;
}

