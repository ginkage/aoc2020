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
            for (int i = 0; i < pass.size(); i++)
                if (pass[i] == alpha && (i == mn-1 || i == mx-1))
                    count++;
            if (count == 1)
                result++;
        }
    }
    cout << result << endl;

    return 0;
}

