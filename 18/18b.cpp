#include "../lib.hpp"

long eval(string &s, int &it);

long factor(string &s, int &it) {
    long res = 0;
    while (it < s.size()) {
        if (s[it] == ' ') {
            it++;
            continue;
        }

        if (s[it] >= '0' && s[it] <= '9') {
            res = s[it++] - '0';
            break;
        }
        else if (s[it] == '(') {
            it++;
            res = eval(s, it);
            break;
        }
        else {
            cout << "Unexpected " << s[it] << endl;
            break;
        }
    }
    return res;
}

long term(string &s, int &it) {
    long res = factor(s, it);
    while (it < s.size()) {
        if (s[it] == ' ') {
            it++;
            continue;
        }

        if (s[it] == '+' || s[it] == '-') {
            char op = s[it++];
            long t = factor(s, it);
            res = (op == '+') ? (res + t) : (res - t);
        }
        else break;
    }
    return res;
}

long eval(string &s, int &it) {
    long res = term(s, it);
    while (it < s.size()) {
        if (s[it] == ' ') {
            it++;
            continue;
        }

        if (s[it] == '*' || s[it] == '/') {
            char op = s[it++];
            long t = term(s, it);
            res = (op == '*') ? (res * t) : (res / t);
        }
        else if (s[it] == ')') {
            it++;
            break;
        }
        else {
            cout << "Unexpected " << s[it] << endl;
            break;
        }
    }
    return res;
}

int main() {
    long result = 0;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        int it = 0;
        result += eval(s, it);
    }
    cout << result << endl;

    return 0;
}

