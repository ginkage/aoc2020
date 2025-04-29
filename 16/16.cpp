#include "../lib.hpp"

struct range_t {
    string name;
    int a1, b1, a2, b2;
    int f;
};

typedef vector<int> ticket_t;

int main() {
    string s;
    smatch linematch;
    vector<range_t> range;
    const regex linerex("(.*): (\\d+)-(\\d+) or (\\d+)-(\\d+)");
    while (true) {
        getline(cin, s);
        if (!cin || !s.size()) break;

        if (regex_match(s, linematch, linerex) && linematch.size() == 6)
            range.push_back(range_t { linematch[1].str(),
                    stoi(linematch[2].str()), stoi(linematch[3].str()),
                    stoi(linematch[4].str()), stoi(linematch[5].str()), -1 });
    }

    getline(cin, s); // "your ticket"
    getline(cin, s);
    ticket_t mine;
    for (string f : split_s(s, ","))
        mine.push_back(stoi(f));
    getline(cin, s); // empty line
    getline(cin, s); // "nearby tickets"

    int n = mine.size();
    long result = 0;
    vector<ticket_t> nearby;

    while (true) {
        getline(cin, s);
        if (!cin) break;
        auto near = split_s(s, ",");
        ticket_t nn;
        bool add = true;
        for (string field : near) {
            int val = stoi(field);
            nn.push_back(val);
            bool good = false;
            for (auto &r : range)
                if ((val >= r.a1 && val <= r.b1) || (val >= r.a2 && val <= r.b2))
                    good = true;
            if (!good) {
                result += val;
                add = false;
            }
        }
        if (add)
            nearby.push_back(nn);
    }
    cout << result << endl;

    vector<vector<int>> match(n, vector<int>(n, 0));
    for (ticket_t &near: nearby) {
        int j = 0;
        for (int val : near) {
            int i = 0;
            for (auto &r : range) {
                if ((val >= r.a1 && val <= r.b1) || (val >= r.a2 && val <= r.b2))
                    match[i][j]++;
                i++;
            }
            j++;
        }
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            match[i][j] = (match[i][j] == nearby.size());

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            int m = 0, l = -1;
            for (int j = 0; j < n; j++)
                if (match[i][j]) {
                    m++;
                    l = j;
                }
            if (m == 1) {
                range[i].f = l;
                for (int t = 0; t < n; t++)
                    match[t][l] = 0;
                break;
            }
        }
    }

    uint64_t mul = 1;
    for (int i = 0; i < n; i++)
        if (range[i].name.rfind("departure", 0) == 0)
            mul *= mine[range[i].f];
    cout << mul << endl;

    return 0;
}

