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
        std::cout << 
        "Commands:\n"
        "skidjular init\n"
            "\tcreates a skidjular directory in $(pwd)\n"
        "skidjular proj add $(name)\n"
            "\tAdds $(name) to list of projects.\n"
        "skidjular proj rm $(name)\n"
            "\tRemoves $(name) from list of projects.\n"
        "skidjular proj list/ls\n"
            "\tOutputs to stdout the project list.\n"
        "skidjular skids init\n"
            "\tcreates the next uncreated week.\n"
        "skidjular skids init now\n"
            "\tForce creates the week.\n"
        "skidjular skids this\n"
            "\tOutputs to stdout this week's project.\n"
        "skidjular skids set $(day) $(proj)\n"
            "\tSets this week's $(day) to $(proj)\n"
        "skidjular skids set $(day) $(proj)\n"
            "\tSets this week's $(day) to $(proj)\n"
        "skidjular skids set this lazy\n"
            "\tForce sets this week's project automatically.\n"
        "skidjular skids set lazy\n"
            "\tSets next unset week's projects automatically.\n"
        "skidjular set i/interactive\n"
            "\tsets next unset week's projects interactively.\n"
        "skidjular history\n"
            "\toutputs to stdout the history.\n"
        "skidjular info\n"
            "\toutpus to stdout information about skids directory"  
        << std::endl;
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
