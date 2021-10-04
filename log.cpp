template<class TLog>
void log(std::string & msg, TLog log) {
    log(msg);
}

void error(std::string & msg) {
    // TODO: call log function so that msg would be printed to std::cerr. use function pointer
}

void file(std::string & msg) {
    // TODO: call log function so that msg would be printed to file log.txt . use functor
    // TODO: how to work with files: https://www.cplusplus.com/doc/tutorial/files/
}

void info(std::string & msg) {
    // TODO: call log function so that msg would be printed to std::cout. use lambda
}

int main(int argc, char const *argv[]) {
    error("error!");
    file("file!");
    info("info!");
    return 0;
}
