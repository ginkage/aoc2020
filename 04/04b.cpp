#include "../lib.hpp"

/*
byr (Birth Year) - four digits; at least 1920 and at most 2002.
iyr (Issue Year) - four digits; at least 2010 and at most 2020.
eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
hgt (Height) - a number followed by either cm or in:
If cm, the number must be at least 150 and at most 193.
If in, the number must be at least 59 and at most 76.
hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
pid (Passport ID) - a nine-digit number, including leading zeroes.
cid (Country ID) - ignored, missing or not.
*/

int main() {
    smatch linematch;
    const regex linerex("(byr):(\\d{4})|(iyr):(\\d{4})|(eyr):(\\d{4})|(hgt):(\\d+)(in|cm)|(hcl):#([0-9a-f]{6})|(ecl):(amb|blu|brn|gry|grn|hzl|oth)|(pid):(\\d{9})");
    vector<map<string, string>> pass;
    pass.push_back(map<string, string>());

    vector<int> keys { 1, 3, 5, 7, 10, 12, 14 };

    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        if (!s.size()) {
            pass.push_back(map<string, string>());
            continue;
        }

        for (string ss : split_s(s, " "))
            if (regex_match(ss, linematch, linerex) && linematch.size() == 16)
                for (int i : keys)
                    if (linematch[i].str().size() != 0) {
                        string key = linematch[i].str();
                        string val = linematch[i+1].str();
                        bool good = false;
                        if (key == "byr") {
                            int year = stoi(linematch[i+1].str());
                            if (year >= 1920 && year <= 2002)
                                good = true;
                        }
                        else if (key == "iyr") {
                            int year = stoi(linematch[i+1].str());
                            if (year >= 2010 && year <= 2020)
                                good = true;
                        }
                        else if (key == "eyr") {
                            int year = stoi(linematch[i+1].str());
                            if (year >= 2020 && year <= 2030)
                                good = true;
                        }
                        else if (key == "hgt") {
                            int height = stoi(linematch[i+1].str());
                            string unit = linematch[i+2].str();
                            if ((unit == "cm" && height >= 150 && height <= 193) ||
                                    (unit == "in" && height >= 59 && height <= 76))
                                good = true;
                        }
                        else
                            good = true;

                        if (good)
                            pass.back()[key] = val;
                    }
    }

    int result = 0;
    for (auto &p : pass)
        if (p.size() == 7)
            result++;
    cout << result << endl;

    return 0;
}

