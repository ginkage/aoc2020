#include "../lib.hpp"

int main() {
    vector<int64_t> input;
    while (cin) {
        int64_t num;
        cin >> num;
        if (!cin) break;
        input.push_back(num);
    }

    int64_t target;
    unordered_map<int64_t, int> numset;
    list<int64_t> numlist;
    for (int64_t num : input) {
        if (numlist.size() == 25) {
            bool good = false;
            for (int64_t k : numlist) {
                int comp = num - k;
                if (comp != k && numset[comp] > 0)
                    good = true;
            }
            if (!good) {
                target = num;
                break;
            }

            numset[numlist.front()]--;
            numlist.pop_front();
        }

        numlist.push_back(num);
        numset[num]++;
    }

    cout << target << endl;

    int64_t sum = 0;
    int start = 0;
    for (int i = 0; i < input.size(); i++) {
        sum += input[i];
        while (sum > target)
            sum -= input[start++];
        if (sum == target && i != start) {
            int64_t mn = sum, mx = 0;
            for (int j = start; j <= i; j++) {
                mn = min(mn, input[j]);
                mx = max(mx, input[j]);
            }
            cout << mn + mx << endl;
            break;
        }
    }

    return 0;
}

