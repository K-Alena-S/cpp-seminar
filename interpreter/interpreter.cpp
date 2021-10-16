#include <iostream>
#include <cstdint>
#include <cassert>


class Command {
 public:
    virtual void apply(const char * c, uint8_t * ptr) {
        std::cout << "Hello from command" << std::endl;
    }
};

class Add: public Command {
    void apply(const char * c, uint8_t * ptr) override {
        (*ptr)++;
    }
};

class Sub: public Command {
    void apply(const char * c, uint8_t * ptr) override {
        std::cout << "Hello from sub" << std::endl;
        // (*ptr)--;
    }
};

class Right: public Command {
    void apply(const char * c, uint8_t * ptr) override {
        ptr++;
    }
};

class Left: public Command {
    void apply(const char * c, uint8_t * ptr) override {
        ptr--;
    }
};

class Write: public Command {
    void apply(const char * c, uint8_t * ptr) override {
        std::cout << unsigned(*ptr) << std::endl;
    }
};

class Read: public Command {
    void apply(const char * c, uint8_t * ptr) override {
        std::cin >> (*ptr);
    }
};

Command * get_cmd(char c) {
    switch (c) {
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
        default:
            assert(false);
    }
}

void interpret(const char * c, uint8_t * ptr) {
    while (*c != '\0') {
        Command * command = get_cmd(*c);
        command->apply(c, ptr);

        // switch (*c) {
        //     case '+':
        //         (*ptr)++;
        //         break;
        //     case '-':
        //         (*ptr)--;
        //         break;
        //     case '>':
        //         ptr++;
        //         break;
        //     case '<':
        //         ptr--;
        //         break;
        //     case '.':
        //         std::cout << unsigned(*ptr) << std::endl;
        //         break;
        //     case ',':
        //         std::cin >> (*ptr);
        //         break;
        //     // case '[':
        //     //     if (*ptr != 0) break;
        //     //     do {
        //     //         c++;
        //     //     } while (*c != ']' && *c != '\0');
        //     //     assert(*c != '\0');
        //     //     break;
        //     // case ']':
        //     //     if (*ptr == 0) break;
        //     //     // TODO: handle no [
        //     //     do {
        //     //         c--;
        //     //     } while (*c != '[');
        //     //     break;
        //     default:
        //         assert(false);
        // }
        c++;
    }
}

int main(int argc, char const *argv[]) {
    Sub s = Sub();
    Command * sub = &s;
    char c = 'c';
    uint8_t data[100] = {};
    // sub->apply(&c, data);
    size_t vptr = *(size_t *) sub;
    typedef void (*apply_t) (const char * c, uint8_t * ptr);
    apply_t func = *(apply_t *) vptr;
    func(&c, data);


    // std::string cmds;
    // uint8_t data[100] = {};
    // uint8_t * ptr = data;
    // while (true) {
    //     std::cin >> cmds;
    //     const char * s = cmds.c_str();
    //     const char * c = s;
    //     interpret(c, ptr);
    // }
    return 0;
}
