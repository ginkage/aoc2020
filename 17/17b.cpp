#include "../lib.hpp"

typedef Eigen::Vector4i v4;

struct V4Hash {
    size_t operator ()(const v4& k) const {
        return (((uint64_t)k[3] & 0xFFFFllu) << 42) + (((uint64_t)k[2] & 0xFFFFllu) << 42) + (((uint64_t)k[1] & 0xFFFFllu) << 21) + ((uint64_t)k[0] & 0xFFFFllu);
    }
};

vector<v4> next_to(v4 p) {
    vector<v4> res;
    int i = p[0], j = p[1], k = p[2], l = p[3], adj = 0;
    for (int di = -1; di <= 1; di++)
        for (int dj = -1; dj <= 1; dj++)
            for (int dk = -1; dk <= 1; dk++)
                for (int dl = -1; dl <= 1; dl++)
                    if (di != 0 || dj != 0 || dk != 0 || dl != 0)
                        res.emplace_back(i + di, j + dj, k + dk, l + dl);
    return res;
}

unordered_set<v4, V4Hash> alive;

bool will_live(v4 p) {
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
                alive.emplace(i, j, 0, 0);

    for (int t = 0; t < 6; t++) {
        unordered_set<v4, V4Hash> next;
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

