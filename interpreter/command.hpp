#ifndef COMMAND_H
#define COMMAND_H

#include <algorithm>
#include <iostream>
#include <vector>
#include "data_it.hpp"

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

#endif