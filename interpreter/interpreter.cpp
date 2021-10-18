#include <iostream>
#include <cstdint>
#include <cassert>
#include <vector>
#include <algorithm>


class Command {
 public:
    virtual void apply(uint8_t * ptr) = 0;
};

class Add: public Command {
    void apply(uint8_t * ptr) override {
        (*ptr)++;
    }
};

class Sub: public Command {
    void apply(uint8_t * ptr) override {
        (*ptr)--;
    }
};

class Right: public Command {
    void apply(uint8_t * ptr) override {
        ptr++;
    }
};

class Left: public Command {
    void apply(uint8_t * ptr) override {
        ptr--;
    }
};

class Write: public Command {
    void apply(uint8_t * ptr) override {
        std::cout << unsigned(*ptr) << std::endl;
    }
};

class Read: public Command {
    void apply(uint8_t * ptr) override {
        std::cin >> (*ptr);
    }
};

class While: public Command {
 public:
    While(std::vector<Command *> cmds): _cmds(cmds) {}
    void apply(uint8_t * ptr) override {
        while (*ptr != 0) {
            std::for_each(_cmds.begin(), _cmds.end(), [&ptr](Command * cmd){ cmd->apply(ptr); });
        }
    }
 private:
    std::vector<Command *> _cmds;
};

class Interpreter {
 public:
    void interpret(std::string & cmds);
 private:
    Command * get_cmd(const char * c);
    uint8_t _data[100];
    uint8_t * _ptr = _data;
};

Command * Interpreter::get_cmd(const char * c) {
    switch (*c) {
        case '+':
            return new Add();
        case '-':
            return new Sub();
        case '>':
            return new Right();
        case '<':
            return new Left();
        case '.':
            return new Write();
        case ',':
            return new Read();
        case '[': {
            std::vector<Command *> cmds;
            while (*c != ']' || *c != '\0') {
                cmds.push_back(get_cmd(c));
                c++;
            }
            assert(c != '\0');
            return new While(cmds);
        }
        default:
            assert(false);
    }
}

void Interpreter::interpret(std::string & cmds) {
    const char * c = cmds.c_str();
    while (*c != '\0') {
        Command * command = get_cmd(c);
        command->apply(_ptr);
        c++;
    }
}

int main(int argc, char const *argv[]) {
    std::string cmds;
    Interpreter interpreter;
    while (true) {
        std::cin >> cmds;
        interpreter.interpret(cmds);
    }
    return 0;
}
