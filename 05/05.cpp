#include "../lib.hpp"

int main() {
    int mx = 0;
    set<int> seat;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        string srow = s.substr(0, 7);
        string scol = s.substr(7, 3);

        int row = 0, col = 0;
        for (char c : srow) {
            row <<= 1;
            if (c == 'B')
                row++;
        }

        for (char c : scol) {
            col <<= 1;
            if (c == 'R')
                col++;
        }

        mx = max(mx, (row * 8) + col);
        seat.emplace(row * 8 + col);
    }
    cout << mx << endl;

    for (int id = 0; id <= 1023; id++)
        if (seat.find(id) == seat.end() && seat.find(id - 1) != seat.end() && seat.find(id + 1) != seat.end())
            cout << id << endl;

    return 0;
}

