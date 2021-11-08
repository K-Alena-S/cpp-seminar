#include "interpreter.hpp"
#include <map>
#include <sstream>

Command * Interpreter::get_cmd(std::string::iterator & it, std::string::iterator & end) {
    std::map<char, creator_t>::iterator creator_it = _creators.find(*it);
    if (creator_it == _creators.end()) {
        std::stringstream ss;
        ss << "no such command: '" << *it << "'";
        throw interpreter_error(ss.str());
    }
    creator_t creator = (*creator_it).second;
    return creator(it, end);
}

void Interpreter::interpret(std::string & cmds) {
    std::string::iterator it = cmds.begin();
    std::string::iterator end = cmds.end();
    while (it != end) {
        try {
            Command * command = get_cmd(it, end);
            command->apply(_it);
        } catch (interpreter_error & e) {
            std::cout << e.what() << std::endl;
        }
        it++;
    }
}