#include "../lib.hpp"

vector<v3> next_to(v3 p) {
    vector<v3> res;
    int i = p[0], j = p[1], k = p[2], adj = 0;
    for (int di = -1; di <= 1; di++)
        for (int dj = -1; dj <= 1; dj++)
            for (int dk = -1; dk <= 1; dk++)
                if (di != 0 || dj != 0 || dk != 0)
                    res.emplace_back(i + di, j + dj, k + dk);
    return res;
}

unordered_set<v3, V3Hash> alive;

bool will_live(v3 p) {
    bool is_alive = alive.find(p) != alive.end();
    int adj = 0;
    for (auto np : next_to(p))
        if (alive.find(np) != alive.end())
            adj++;
    return (is_alive && adj == 2) || (adj == 3);
}

int main() {
    vector<string> grid;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        grid.push_back(s);
    }

    int m = grid.size(), n = grid[0].size();
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (grid[i][j] == '#')
                alive.emplace(i, j, 0);

    for (int t = 0; t < 6; t++) {
        unordered_set<v3, V3Hash> next;
        for (auto &p : alive) {
            if (will_live(p))
                next.insert(p);
            for (auto np : next_to(p))
                if (will_live(np))
                    next.insert(np);
        }
        swap(alive, next);
    }

    cout << alive.size() << endl;

    return 0;
}

