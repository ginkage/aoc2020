#include "../lib.hpp"

enum dir_t {
    dir_north,
    dir_east,
    dir_south,
    dir_west
};

struct side_t {
    string s;
    int adj;
};

struct tile_t {
    int id;
    vector<string> grid;
    vector<side_t> sides; // N, E, S, W
};

void flip_v(tile_t &t) {
    reverse(t.grid.begin(), t.grid.end());
    swap(t.sides[dir_north], t.sides[dir_south]);
    reverse(t.sides[dir_east].s.begin(), t.sides[dir_east].s.end());
    reverse(t.sides[dir_west].s.begin(), t.sides[dir_west].s.end());
}

void flip_h(tile_t &t) {
    for (string &s : t.grid)
        reverse(s.begin(), s.end());
    swap(t.sides[dir_east], t.sides[dir_west]);
    reverse(t.sides[dir_north].s.begin(), t.sides[dir_north].s.end());
    reverse(t.sides[dir_south].s.begin(), t.sides[dir_south].s.end());
}

void rotate90(tile_t &t) { // CCW
    for (int i = 0; i < 5; i++)
        for (int j = i; j < 9 - i; j++) {
            int c1 = t.grid[i][j];
            int c2 = t.grid[j][9 - i];
            int c3 = t.grid[9 - i][9 - j];
            int c4 = t.grid[9 - j][i];
            t.grid[i][j] = c2;
            t.grid[j][9 - i] = c3;
            t.grid[9 - i][9 - j] = c4;
            t.grid[9 - j][i] = c1;
         }

    vector<side_t> tmp = t.sides;
    t.sides[dir_north] = tmp[dir_east];
    t.sides[dir_east] = tmp[dir_south];
    t.sides[dir_south] = tmp[dir_west];
    t.sides[dir_west] = tmp[dir_north];
    reverse(t.sides[dir_east].s.begin(), t.sides[dir_east].s.end());
    reverse(t.sides[dir_west].s.begin(), t.sides[dir_west].s.end());
}

int main() {
    vector<tile_t> tiles;
    const regex linerex("Tile (.*):");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 2) {
            int id = stoi(linematch[1].str());
            vector<string> grid;
            for (int i = 0; i < 10; i++) {
                getline(cin, s);
                grid.push_back(s);
            }
            getline(cin, s);
            tiles.push_back(tile_t {});
            tiles.back().id = id;
            tiles.back().grid = grid;
        }
    }

    for (tile_t &tile : tiles) {
        string side;
        for (int i = 0; i < 10; i++)
            side += tile.grid[0][i];
        tile.sides.push_back(side_t { side, -1 });

        side = "";
        for (int i = 0; i < 10; i++)
            side += tile.grid[i][9];
        tile.sides.push_back(side_t { side, -1 });

        side = "";
        for (int i = 0; i < 10; i++)
            side += tile.grid[9][i];
        tile.sides.push_back(side_t { side, -1 });

        side = "";
        for (int i = 0; i < 10; i++)
            side += tile.grid[i][0];
        tile.sides.push_back(side_t { side, -1 });
    }

    for (int i = 0; i < tiles.size(); i++) {
        tile_t &ti = tiles[i];
        for (int j = i + 1; j < tiles.size(); j++) {
            tile_t &tj = tiles[j];
            bool match = false;
            for (side_t &si : ti.sides) {
                for (side_t &sj : tj.sides)
                    if (si.s == sj.s || si.s == string(sj.s.rbegin(), sj.s.rend())) {
                        si.adj = j;
                        sj.adj = i;
                        match = true;
                        break;
                    }
                if (match)
                    break;
            }
        }
    }

    int start = -1;
    long result = 1;
    int i = 0;
    for (tile_t &tile : tiles) {
        int count = 0;
        for (side_t &side : tile.sides)
            if (side.adj != -1)
                count++;
        if (count == 2) {
            start = i;
            result *= tile.id;
        }
        i++;
    }
    cout << result << endl;

    vector<string> grid(96, string(96, ' '));
    int next = start, prev = -1;
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            tile_t &t = tiles[next];
            if (i == 0 && j == 0) {
                while (t.sides[dir_east].adj == -1 || t.sides[dir_south].adj == -1)
                    rotate90(t);
            }
            else if (j > 0) {
                while (t.sides[dir_west].adj != prev)
                    rotate90(t);
                if (t.sides[dir_west].s != tiles[prev].sides[dir_east].s)
                    flip_v(t);
            }
            else {
                while (t.sides[dir_north].adj != prev)
                    rotate90(t);
                if (t.sides[dir_north].s != tiles[prev].sides[dir_south].s)
                    flip_h(t);
            }

            if (j == 0) start = next;
            prev = j == 11 ? start : next;
            next = j == 11 ? tiles[start].sides[dir_south].adj : t.sides[dir_east].adj;

            for (int gi = 1; gi < 9; gi++)
                for (int gj = 1; gj < 9; gj++)
                    grid[i * 8 + gi - 1][j * 8 + gj - 1] = t.grid[gi][gj];
        }
    }

    string temp[3] = {
        "                  # ",
        "#    ##    ##    ###",
        " #  #  #  #  #  #   "
    };

    int found = 0;
    for (int k = 0; k < 8; k++) {
        for (int i = 0; i < grid.size() - 3; i++) {
            for (int j = 0; j < grid[i].size() - 20; j++) {
                bool good = true;
                for (int gi = 0; gi < 3 && good; gi++)
                    for (int gj = 0; gj < 20 && good; gj++)
                        if (temp[gi][gj] == '#' && grid[i+gi][j+gj] != '#')
                            good = false;
                if (good)
                    found++;
            }
        }

        if (k == 3)
            reverse(grid.begin(), grid.end());
        else {
            for (int i = 0; i < 48; i++)
                for (int j = i; j < 95 - i; j++) {
                    int c1 = grid[i][j];
                    int c2 = grid[j][95 - i];
                    int c3 = grid[95 - i][95 - j];
                    int c4 = grid[95 - j][i];
                    grid[i][j] = c2;
                    grid[j][95 - i] = c3;
                    grid[95 - i][95 - j] = c4;
                    grid[95 - j][i] = c1;
                }
        }
    }

    int total = 0;
    for (string &s : grid)
        for (char c : s)
            if (c == '#')
                total++;
    cout << total - found * 15 << endl;

    return 0;
}

