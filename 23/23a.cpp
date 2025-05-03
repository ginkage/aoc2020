#include "../lib.hpp"

int main() {
    vector<int> ring { 3, 6, 2, 9, 8, 1, 7, 5, 4 };
    //vector<int> ring { 3, 8, 9, 1, 2, 5, 4, 6, 7 };

    int n = ring.size();
    vector<int> id;
    vector<int> next;
    vector<int> pos(n + 1);

    for (int i = 0; i < n; i++) {
        id.push_back(ring[i]);
        next.push_back((i + 1) % n);
        pos[ring[i]] = i;
    }

    int cur = 0;
    for (int t = 0; t < 100; t++) {
        int dest = id[cur];
        int ni1 = next[cur], ni2 = next[ni1], ni3 = next[ni2];
        int n1 = id[ni1], n2 = id[ni2], n3 = id[ni3];

        do {
            dest--;
            if (dest < 1)
                dest = n;
        } while (dest == n1 || dest == n2 || dest == n3);

        int di = pos[dest], nd = next[di], nt = next[ni3];
        next[cur] = nt;
        next[ni3] = nd;
        next[di] = ni1;
        cur = nt;
    }

    int j = next[pos[1]];
    for (int i = 0; i < n - 1; i++) {
        cout << id[j];
        j = next[j];
    }
    cout << endl;

    return 0;
}

