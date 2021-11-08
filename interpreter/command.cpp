#include "command.hpp"
#include "interpreter.hpp"

namespace {

    Command * add_creator(std::string::iterator & it, std::string::iterator & end) {
        return new Add();
    }

    bool add_cmd = Interpreter::getInstance().registerCreator('+', add_creator);

    Command * sub_creator(std::string::iterator & it, std::string::iterator & end) {
        return new Sub();
    }

    bool sub_cmd = Interpreter::getInstance().registerCreator('-', sub_creator);

    Command * right_creator(std::string::iterator & it, std::string::iterator & end) {
        return new Right();
    }

    bool right_cmd = Interpreter::getInstance().registerCreator('>', right_creator);

    Command * left_creator(std::string::iterator & it, std::string::iterator & end) {
        return new Left();
    }

    bool left_cmd = Interpreter::getInstance().registerCreator('<', left_creator);

    Command * write_creator(std::string::iterator & it, std::string::iterator & end) {
        return new Write();
    }

    bool write_cmd = Interpreter::getInstance().registerCreator('.', write_creator);

    Command * read_creator(std::string::iterator & it, std::string::iterator & end) {
        return new Read();
    }

    bool read_cmd = Interpreter::getInstance().registerCreator(',', read_creator);

    Command * while_creator(std::string::iterator & it, std::string::iterator & end) {
        std::vector<Command *> cmds;
        it++;
        while (it != end && *it != ']') {
            cmds.push_back(Interpreter::getInstance().get_cmd(it, end));
            it++;
        }
        assert(it != end);
        return new While(cmds);
    }

    bool while_cmd = Interpreter::getInstance().registerCreator('[', while_creator);
};