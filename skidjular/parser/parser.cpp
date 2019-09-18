#include "parser.h"

Parser::Parser(int argc, char* args[]) {
    if (argc <= 1) {
        std::cout << "Usage: skidjular --help or -h\n";
        exit(1);
    }

    for (int i = 1; i < argc; i++)
        this->m_parsedArgs.push_back(args[i]);
}
Parser::~Parser(void) {}

auto Parser::get()->std::vector<std::string> {
    return this->m_parsedArgs;
}
