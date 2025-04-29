#include "../lib.hpp"

int main() {
    vector<string> grid, next;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        grid.push_back(s);
        next.push_back(s);
    }

    int m = grid.size(), n = grid[0].size();

    for (int t = 0; t < 10000; t++) {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                int adj = 0;
                for (int di = -1; di <= 1; di++)
                    for (int dj = -1; dj <= 1; dj++)
                        if (di != 0 || dj != 0) {
                            for (int k = 1; k <= m; k++) {
                                int ni = i + di * k, nj = j + dj * k;
                                if (ni >= 0 && nj >= 0 && ni < m && nj < n) {
                                    if (grid[ni][nj] != '.') {
                                        adj += (grid[ni][nj] == '#');
                                        break;
                                    }
                                }
                                else break;
                            }
                        }
                if (grid[i][j] == 'L' && adj == 0)
                    next[i][j] = '#';
                else if (grid[i][j] == '#' && adj >= 5)
                    next[i][j] = 'L';
                else next[i][j] = grid[i][j];
            }
        swap(grid, next);
        if (grid == next) break;
        //for (int i = 0; i < m; i++)
        //    cout << grid[i] << endl;
        //cout << endl;
    }

    int result = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (grid[i][j] == '#')
                result++;
    cout << result << endl;

    return 0;
}

