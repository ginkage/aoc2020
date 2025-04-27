#include "../lib.hpp"

int main() {
    smatch linematch;
    const regex linerex("(.*):(.*)");
    vector<map<string, string>> pass;
    pass.push_back(map<string, string>());

    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        if (!s.size()) {
            pass.push_back(map<string, string>());
            continue;
        }

        for (string ss : split_s(s, " "))
            if (regex_match(ss, linematch, linerex) && linematch.size() == 3)
                pass.back()[linematch[1].str()] = linematch[2].str();
    }

    int result = 0;
    for (auto &p : pass)
        if (p.size() == 8 || (p.size() == 7 && p.find("cid") == p.end()))
            result++;
    cout << result << endl;

    return 0;
}

