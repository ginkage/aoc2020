#include "../lib.hpp"

char dirs[] = "NWSE";

map<char, vec> dirmap = {
    { 'N', vec(-1, 0) },
    { 'W', vec(0, -1) },
    { 'S', vec(1, 0) },
    { 'E', vec(0, 1) }
};

int main() {
    vec pos(0, 0);
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
                pos += dirmap[dir] * num;
            else if (dir == 'L')
                cur = (cur + num / 90) % 4;
            else if (dir == 'R')
                cur = (cur + 4 - num / 90) % 4;
            else if (dir == 'F')
                pos += dirmap[dirs[cur]] * num;
        }
    }

    cout << (abs(pos[0]) + abs(pos[1])) << endl;

    return 0;
}

