#include "../lib.hpp"

int play(map<int, list<int>> &cards, bool recurse) {
    set<list<int>> met;
    while (cards[1].size() > 0 && cards[2].size() > 0) {
        if (met.find(cards[1]) != met.end()) return 1;
        met.insert(cards[1]);

        int top1 = cards[1].front();
        int top2 = cards[2].front();
        cards[1].pop_front();
        cards[2].pop_front();

        int win = -1;
        if (top1 <= cards[1].size() && top2 <= cards[2].size() && recurse) {
            map<int, list<int>> copy;
            copy_n(cards[1].begin(), top1, back_inserter(copy[1]));
            copy_n(cards[2].begin(), top2, back_inserter(copy[2]));
            win = play(copy, recurse);
        }
        else {
            if (top1 > top2)
                win = 1;
            else
                win = 2;
        }

        if (win == 1) {
            cards[1].push_back(top1);
            cards[1].push_back(top2);
        }
        else {
            cards[2].push_back(top2);
            cards[2].push_back(top1);
        }
    }

    if (cards[1].size() > 0)
        return 1;
    return 2;
}

int main() {
    map<int, list<int>> cards;
    int player;
    const regex linerex("Player (.*):");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 2)
            player = stoi(linematch[1].str());
        else if (s.size() > 0)
            cards[player].push_back(stoi(s));
    }

    long result = 0;
    map<int, list<int>> original = cards;
    int win = play(cards, false);
    int i = cards[win].size();
    for (int c : cards[win]) {
        result += i * c;
        i--;
    }
    cout << result << endl;

    long result2 = 0;
    cards = original;
    win = play(cards, true);
    i = cards[win].size();
    for (int c : cards[win]) {
        result2 += i * c;
        i--;
    }
    cout << result2 << endl;

    return 0;
}

