#include "parser.h"

Parser::Parser(int argc, char** args) {
    if (argc <= 1) {
        std::cout << "Usage: skidjular --help or -h\n";
        exit(1);
    }

    args++;
    for (int i = 0; i < argc-1; i++)
        this->m_parsedArgs.push_back(*(args++));
}
Parser::~Parser(void) {}

auto Parser::get()->std::vector<std::string> {
    return this->m_parsedArgs;
}
