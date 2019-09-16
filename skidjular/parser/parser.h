#pragma once
#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <vector>

class Parser {
    public:
        Parser(int argc, char** args);
        ~Parser(void);
        
        auto get()->std::vector<std::string>;

    private:
        std::vector<std::string> m_parsedArgs;
};

#endif
