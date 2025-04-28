#include "../lib.hpp"

enum op_t {
    op_nop,
    op_acc,
    op_jmp
};

unordered_map<string, op_t> op_name = {
    { "nop", op_nop },
    { "acc", op_acc },
    { "jmp", op_jmp }
};

static int64_t reg_acc;
static int64_t reg_jmp;

struct val_t {
    int64_t val;

    val_t(const string &v) {
        val = stol(v);
    }

    val_t() {}
};

struct cmd_t {
    op_t op;
    val_t arg;
};

unordered_map<op_t, function<void(cmd_t&)>> ops = {
    { op_nop, [](cmd_t &c) { } },
    { op_acc, [](cmd_t &c) { reg_acc += c.arg.val; } },
    { op_jmp, [](cmd_t &c) { reg_jmp = c.arg.val; } }
};

vector<cmd_t> program;

bool is_loop() {
    int64_t ptr = 0;
    reg_acc = 0;
    unordered_set<int64_t> met;
    while (ptr >= 0 && ptr < program.size()) {
        if (met.find(ptr) != met.end())
            return true;
        met.insert(ptr);

        reg_jmp = 1;
        cmd_t &cmd = program[ptr];
        ops[cmd.op](cmd);
        ptr += reg_jmp;
    }

    return false;
}

int main() {
    const regex linerex1("(.*) (.*)");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        cmd_t cmd;
        smatch linematch;
        if (regex_match(s, linematch, linerex1) && linematch.size() == 3) {
            cmd.op = op_name[linematch[1].str()];
            cmd.arg = val_t(linematch[2].str());
        }
        program.push_back(cmd);
    }

    if (is_loop())
        cout << reg_acc << endl;

    for (int i = 0; i < program.size(); i++) {
        program[i].op = (op_t)(2 - program[i].op);
        if (!is_loop()) {
            cout << reg_acc << endl;
            break;
        }
        program[i].op = (op_t)(2 - program[i].op);
    }

    return 0;
}

