#include "../lib.hpp"

int main() {
    vector<long> expense;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        expense.push_back(stol(s));
    }

    for (int i = 0; i < expense.size(); i++)
        for (int j = i + 1; j < expense.size(); j++)
            if (expense[i] + expense[j] == 2020)
                cout << expense[i] * expense[j] << endl;

    for (int i = 0; i < expense.size(); i++)
        for (int j = i + 1; j < expense.size(); j++)
            for (int k = j + 1; k < expense.size(); k++)
                if (expense[i] + expense[j] + expense[k] == 2020)
                    cout << expense[i] * expense[j] * expense[k] << endl;

    return 0;
}

