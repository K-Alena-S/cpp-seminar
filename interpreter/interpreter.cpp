#include "interpreter.hpp"

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