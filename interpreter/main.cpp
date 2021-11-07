#include <string>
#include "interpreter.hpp"

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