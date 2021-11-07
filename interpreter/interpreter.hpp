#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <cassert>
#include "command.hpp"
#include "data_it.hpp"

class Interpreter {
 public:
    void interpret(std::string & cmds);
 private:
    Command * get_cmd(std::string::iterator & it, std::string::iterator & end);
    data_it _it;
};

#endif