#include "../lib.hpp"

int main() {
    vector<int> ring { 3, 6, 2, 9, 8, 1, 7, 5, 4 };
    //vector<int> ring { 3, 8, 9, 1, 2, 5, 4, 6, 7 };

    int n = 1000000;
    vector<long> id(n);
    vector<int> next(n);
    vector<int> pos(n + 1);

    for (int i = 0; i < n; i++) {
        long k = (i < ring.size()) ? ring[i] : (i + 1);
        id[i] = k;
        pos[k] = i;
        next[i] = (i + 1) % n;
    }

    int cur = 0;
    for (int t = 0; t < 10000000; t++) {
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

    int j = next[pos[1]], k = next[j];
    cout << id[j] * id[k] << endl;

    return 0;
}

