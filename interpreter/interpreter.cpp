#include <iostream>
#include <cstdint>
#include <cassert>
#include <vector>
#include <algorithm>
#include <array>
#include <exception>

class interpreter_error: public std::runtime_error {
 public:
    interpreter_error(const char * msg): std::runtime_error(msg) {}
};

class data_it {
 public:    
    uint8_t & operator*() {
        return *_it;
    }

    // куда показывать?
    // что показывать?
    // где обрабатывать?
    data_it & operator++() {
        // TODO: _data.end() - fail
        // 1. assert(_it != _data.end()) : cannot specify output, cannot specify message, cannot handle error
        // 2. errno / return error code : can specify output, can specify message, can handle error but can easily forget
        // 3. exceptions

        // std::exception
        //    - std::runtime_error
        //    - std::logic_error
        if (_it == _data.end()) throw interpreter_error("out of bounds: cannot access element after last");
        ++_it;
        return *this; 
    }

    data_it & operator--() {
        if (_it == _data.begin()) throw interpreter_error("out of bounds: cannot access element before first");
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

void Interpreter::interpret(std::string & cmds) {
    std::string::iterator it = cmds.begin();
    std::string::iterator end = cmds.end();
    while (it != end) {
        Command * command = get_cmd(it, end);
        try {
            command->apply(_it);
        } catch (interpreter_error & e) {
            std::cout << e.what() << std::endl;
        }
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
