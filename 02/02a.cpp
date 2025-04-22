#include "../lib.hpp"

int main() {
    int result = 0;
    const regex linerex("(.*)-(.*) (.): (.*)");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 5) {
            int mn = stoi(linematch[1].str());
            int mx = stoi(linematch[2].str());
            char alpha = linematch[3].str()[0];
            string pass = linematch[4].str();
            int count = 0;
            for (char c : pass)
                if (c == alpha)
                    count++;
            if (count >= mn && count <= mx)
                result++;
        }
    }
    cout << result << endl;

    return 0;
}

