#include "../lib.hpp"

map<string, vector<pair<int, string>>> contents;

bool is_gold(string s) {
    auto it = contents.find(s);
    if (it == contents.end())
        return false;

    for (auto &p : it->second)
        if ((p.second == "shiny gold") || is_gold(p.second))
            return true;
    return false;
}

long count(string s) {
    auto it = contents.find(s);
    if (it == contents.end())
        return 1;

    long result = 0;
    for (auto &p : it->second)
        result += p.first * count(p.second);
    return result + 1;
}

int main() {
    const regex linerex("(.*) bags contain (.*)\\.");
    const regex bagrex("(\\d+) (.*) bag[s]?");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 3) {
            string bag = linematch[1].str();
            for (string c : split_s(linematch[2].str(), ", "))
                if (regex_match(c, linematch, bagrex) && linematch.size() == 3)
                    contents[bag].emplace_back(stoi(linematch[1].str()), linematch[2].str());
        }
    }

    int result = 0;
    for (auto &p : contents)
        if (is_gold(p.first))
            result++;
    cout << result << endl;
    cout << (count("shiny gold") - 1) << endl;

    return 0;
}

