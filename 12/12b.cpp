#include "../lib.hpp"

map<char, vec> dirmap = {
    { 'N', vec(-1, 0) },
    { 'W', vec(0, -1) },
    { 'S', vec(1, 0) },
    { 'E', vec(0, 1) }
};

int main() {
    vec pos(0, 0), wp(-1, 10);
    char cur = 3;
    const regex linerex("(.)(\\d+)");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 3) {
            char dir = linematch[1].str()[0];
            int num = stoi(linematch[2].str());

            if (dirmap.find(dir) != dirmap.end())
                wp += dirmap[dir] * num;
            else if (dir == 'L') {
                num /= 90;
                while (num--)
                    wp = vec(-wp[1], wp[0]);
            }
            else if (dir == 'R') {
                num /= 90;
                while (num--)
                    wp = vec(wp[1], -wp[0]);
            }
            else if (dir == 'F')
                pos += wp * num;
        }
    }

    cout << (abs(pos[0]) + abs(pos[1])) << endl;

    return 0;
}

