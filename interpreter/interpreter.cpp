#include <iostream>
#include <cstdint>
#include <cassert>
#include <vector>
#include <algorithm>
#include <array>

class data_it {
 public:    
    uint8_t & operator*() {
        return *_it;
    }
    data_it & operator++() {
        // TODO: _data.end() - fail
        ++_it;
        return *this; 
    }

    data_it & operator--() {
        // TODO: _data.begin() - fail
        --_it;
        return *this; 
    }
 private:
    std::array<uint8_t, 100> _data = {};
    std::array<uint8_t, 100>::iterator _it = _data.begin();
};

class Command {
 public:
    virtual void apply(data_it & it) = 0;
};

class Add: public Command {
    void apply(data_it & it) override {
        (*it)++;
    }
};

class Sub: public Command {
    void apply(data_it & it) override {
        (*it)--;
    }
};

class Right: public Command {
    void apply(data_it & it) override {
        ++it;
    }
};

class Left: public Command {
    void apply(data_it & it) override {
        --it;
    }
};

class Write: public Command {
    void apply(data_it & it) override {
        std::cout << unsigned(*it) << std::endl;
    }
};

class Read: public Command {
    void apply(data_it & it) override {
        std::cin >> (*it);
    }
};

class While: public Command {
 public:
    While(std::vector<Command *> cmds): _cmds(cmds) {}
    void apply(data_it & it) override {
        while (*it != 0) {
            std::for_each(_cmds.begin(), _cmds.end(), [&it](Command * cmd){ cmd->apply(it); });
        }
    }
 private:
    std::vector<Command *> _cmds;
};

class Interpreter {
 public:
    void interpret(std::string & cmds);
 private:
    Command * get_cmd(std::string::iterator & it, std::string::iterator & end);
    data_it _it;
};

Command * Interpreter::get_cmd(std::string::iterator & it, std::string::iterator & end) {
    switch (*it) {
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
            it++;
            while (it != end && *it != ']') {
                cmds.push_back(get_cmd(it, end));
                it++;
            }
            assert(it != end);
            return new While(cmds);
        }
        default:
            assert(false);
    }
}

// class StrIterator {
//  public:
//     StrIterator(std::string & cmds): _cmds(cmds) {}
//     const char operator*() {
//         return *_c;
//     }
//     StrIterator(std::string & cmds, const char * c): _cmds(cmds), _c(c) {}
//     bool operator!=(StrIterator & other) {
//         if (this == &other) return false;
//         if (&_cmds != &other._cmds) return true;
//         if (_c != other._c) return true;
//         return false;
//     }
//     StrIterator end() {
//         // '\0'
//         const char * last = _cmds.c_str() + (_cmds.size() - 1);
//         return StrIterator(_cmds, last);
//     }
//     StrIterator & operator++() {
//         _c++;
//         return *this;
//     } 
//  private:
//     std::string & _cmds;
//     const char * _c = _cmds.c_str();
// };

void Interpreter::interpret(std::string & cmds) {
    std::string::iterator it = cmds.begin();
    std::string::iterator end = cmds.end();
    while (it != end) {
        Command * command = get_cmd(it, end);
        command->apply(_it);
        it++;
    }
}

int main(int argc, char const *argv[]) {
    std::string cmds;
    Interpreter interpreter;
    while (true) {
        std::cout << "> ";
        std::cin >> cmds;
        interpreter.interpret(cmds);
    }
    return 0;
}
