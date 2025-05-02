#include "../lib.hpp"

int main() {
    unordered_map<int, string> name;
    unordered_map<int, int> count;
    map<string, unordered_set<int>> alrgn;
    const regex linerex("(.*) \\(contains (.*)\\)");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 3) {
            unordered_set<int> ingrd;
            for (string s : split_s(linematch[1].str(), " ")) {
                int i = remap(s);
                name[i] = s;
                ingrd.insert(i);
                count[i]++;
            }

            for (string s : split_s(linematch[2].str(), ", ")) {
                unordered_set<int> next;
                if (alrgn.find(s) == alrgn.end())
                    next = ingrd;
                else
                    for (int i : alrgn[s])
                        if (ingrd.find(i) != ingrd.end())
                            next.insert(i);
                alrgn[s] = next;
            }
        }
    }

    unordered_map<string, int> exact;
    unordered_set<int> found;
    bool prune = true;
    while (prune) {
        prune = false;
        for (auto &p : alrgn)
            if (p.second.size() == 1) {
                int ingr = *(p.second.begin());
                exact[p.first] = ingr;
                found.insert(ingr);
                for (auto &r : alrgn)
                    r.second.erase(ingr);
                prune = true;
                break;
            }
    }

    int result = 0;
    for (auto &p : count)
        if (found.find(p.first) == found.end())
            result += p.second;
    cout << result << endl;

    for (auto &p : alrgn)
        cout << name[exact[p.first]] << ',';
    cout << endl;

    return 0;
}

