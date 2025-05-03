#include "../lib.hpp"

unordered_map<string, vec> delta {
    { "e", vec(1, 1) },
    { "se", vec(1, 0) },
    { "sw", vec(0, -1) },
    { "w", vec(-1, -1) },
    { "nw", vec(-1, 0) },
    { "ne", vec(0, 1) }
};

int main() {
    unordered_map<vec, bool, VHash> black;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        vec pos(0, 0);
        for (int i = 0; i < s.size(); i++) {
            string dir;
            dir += s[i];
            if (s[i] == 's' || s[i] == 'n')
                dir += s[++i];
            pos += delta[dir];
        }
        black[pos] = !black[pos];
    }

    int result = 0;
    for (auto &p : black)
        if (p.second)
            result++;
    cout << result << endl;

    for (int t = 0; t < 100; t++) {
        unordered_map<vec, bool, VHash> next;
        unordered_set<vec, VHash> look;

        for (auto &p : black)
            if (p.second) {
                look.insert(p.first);
                for (auto &d : delta)
                    look.insert(p.first + d.second);
            }

        for (const vec &p : look) {
            int adj = 0;
            auto it = black.find(p);
            bool b = (it == black.end()) ? false : it->second;
            for (auto &d : delta) {
                vec r = p + d.second;
                auto jt = black.find(r);
                bool q = (jt == black.end()) ? false : jt->second;
                if (q)
                    adj++;
            }

            if (b && (adj == 0 || adj > 2))
                next[p] = false;
            else if (!b && adj == 2)
                next[p] = true;
            else
                next[p] = b;
        }

        swap(black, next);
    }

    result = 0;
    for (auto &p : black)
        if (p.second)
            result++;
    cout << result << endl;

    return 0;
}

