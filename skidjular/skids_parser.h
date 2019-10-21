#ifndef SKIDS_PARSER_h
#define SKIDS_PARSER_h

#include <string>
#include <vector>
#include <array>
#include <map>
#include <functional>

#include "skids_parserdef.h"

namespace skidsParser {
    static void printHelp(void) {
        std::cout << "This is help to be implemented." << std::endl;
    }

    static void dispatch(Command cmd) {
        try {
        auto index = skidsParser::s_funcsIDMap.at(cmd.s_cmd);
        auto f = skidsParser::s_funcsArr[index];
        f();
        } catch (const std::exception& e) {
            std::cout << "ERROR: Could not dispatch command: " << cmd.s_cmd << "." << std::endl;
            printHelp();
            exit(1);
        }
    }

    [[nodiscard]] static bool isKnownKeyWord(const std::string word) {
        if (word == special::keywords::init)
            return true;
        else if (word == special::keywords::history)
            return true;
         else if (word == special::keywords::info)
            return true;
        else if (word == special::keywords::proj)
            return true;
        else if (word == special::keywords::add)
            return true;
        else if (word == special::keywords::rm)
            return true;
        else if (word == special::keywords::list1)
            return true;
        else if (word == special::keywords::list2)
            return true;
        else if (word == special::keywords::skids)
            return true;
        else if (word == special::keywords::now)
            return true;
        else if (word == special::keywords::This)
            return true;
        else if (word == special::keywords::set)
            return true;
        else if (word == special::keywords::lazy)
            return true;
        else if (word == special::keywords::interactive1)
            return true;
        else if (word == special::keywords::interactive2)
            return true;
        return false;
    }

    [[nodiscard]] static auto buildCmd(int argc, char *argv[]) {
        std::vector<std::string> args;
        Command result;
        for (int i = 1; i < argc; i++)
            args.push_back(argv[i]);
        
        std::string cmd;
        for (auto term : args) {
            if (isKnownKeyWord(term))
                cmd += term;
            else if (result.s_name1Reg == "")
                result.s_name1Reg = term;
            else if (result.s_name2Reg == "")
                result.s_name1Reg = term;
        }

        result.s_cmd = cmd;
        return result;
    }
}

#endif
