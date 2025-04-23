#include "../lib.hpp"

int main() {
    vector<string> grid;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        grid.push_back(s);
    }

    int m = grid.size(), n = grid[0].size();
    long r1 = 0, r2 = 0, r3 = 0, r4 = 0, r5 = 0;
    for (int i = 0; i < m; i++)
        if (grid[i][i%n] == '#')
            r1++;
    for (int i = 0; i < m; i++)
        if (grid[i][(i*3)%n] == '#')
            r2++;
    for (int i = 0; i < m; i++)
        if (grid[i][(i*5)%n] == '#')
            r3++;
    for (int i = 0; i < m; i++)
        if (grid[i][(i*7)%n] == '#')
            r4++;
    for (int i = 0; i < m; i+=2)
        if (grid[i][(i/2)%n] == '#')
            r5++;
    cout << r2 << ' ' << (r1*r2*r3*r4*r5) << endl;

    return 0;
}

