#ifndef INTERPRETER_ERROR_H
#define INTERPRETER_ERROR_H

#include <stdexcept>

class interpreter_error: public std::runtime_error {
 public:
    interpreter_error(std::string msg): std::runtime_error(msg) {}
};

#endif