#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <cassert>
#include <map>
#include "command.hpp"
#include "data_it.hpp"

class Interpreter {
 public:
    static Interpreter & getInstance() {
        static Interpreter i;
        return i;
    }
    typedef Command * (*creator_t)(std::string::iterator & it, std::string::iterator & end);
    bool registerCreator(char c, creator_t creator) {
        _creators[c] = creator;
        return true;
    }
    Command * get_cmd(std::string::iterator & it, std::string::iterator & end);
    void interpret(std::string & cmds);
 private:
    Interpreter() = default;
    std::map<char, creator_t> _creators;
    data_it _it;
};

#endif