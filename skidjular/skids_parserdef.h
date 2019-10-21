#ifndef SKIDS_PARSERDEFS_h
#define SKIDS_PARSERDEFS_h

#include <string>
#include <vector>
#include <array>
#include <map>
#include <functional>

#include "skids_funcs.h" 

namespace skidsParser {
    namespace special {
        constexpr auto name = "$name";
        constexpr auto day = "$day";
        constexpr auto opt = "$opt";
        namespace keywords {
            constexpr auto init = "init";
            constexpr auto history = "history";
            constexpr auto info = "info";
            constexpr auto proj = "proj";
            constexpr auto add = "add";
            constexpr auto rm = "rm";
            constexpr auto list1 = "ls";
            constexpr auto list2 = "list";
            constexpr auto skids = "skids";
            constexpr auto now = "now";
            constexpr auto This = "this";
            constexpr auto set = "set";
            constexpr auto lazy = "lazy";
            constexpr auto interactive1 = "i";
            constexpr auto interactive2 = "interactive";
        }
    }
    namespace cmds {
        constexpr auto init = "init";
        constexpr auto history = "history";
        constexpr auto info = "info";
        namespace proj {
            constexpr auto add = "proj add $name";
            constexpr auto rm = "proj rm $name";
            constexpr auto list1 = "proj ls";
            constexpr auto list2 = "proj list";
        }
        namespace skids {
            constexpr auto init = "skids init";
            constexpr auto initNow = "skids init now";
            constexpr auto now = "skids now";
            constexpr auto This = "skids this";
            constexpr auto set = "skids set $day $name";
            constexpr auto setThis = "skids set this $day $name";
            constexpr auto setLazy = "skids set lazy";
            constexpr auto setThisLazy = "skids set this lazy";
            constexpr auto setInteractive1 = "skids set i";
            constexpr auto setInteractive2 = "skids set interactive";
        }
    }

    enum cmdsID {
        init = 0,
        history = 1,
        info = 2,
        proj_add,
        proj_rm,
        proj_list,
        skids_init,
        skids_initNow,
        skids_now,
        skids_set,
        skids_setThis,
        skids_setLazy,
        skids_setThisLazy,
        skids_setInteractive,
    };

    const static std::map<std::string, int> s_funcsIDMap = {{
        { std::make_pair(skidsParser::cmds::init, cmdsID::init) },
        { std::make_pair(skidsParser::cmds::history, cmdsID::history) },
        { std::make_pair(skidsParser::cmds::info, cmdsID::info) },
        { std::make_pair(skidsParser::cmds::proj::add, cmdsID::proj_add) },
        { std::make_pair(skidsParser::cmds::proj::rm, cmdsID::proj_rm) },
        { std::make_pair(skidsParser::cmds::proj::list1, cmdsID::proj_list) },
        { std::make_pair(skidsParser::cmds::proj::list2, cmdsID::proj_list) },
        { std::make_pair(skidsParser::cmds::skids::init, cmdsID::skids_init) },
        { std::make_pair(skidsParser::cmds::skids::initNow, cmdsID::skids_initNow) },
        { std::make_pair(skidsParser::cmds::skids::now, cmdsID::skids_now) },
        { std::make_pair(skidsParser::cmds::skids::set, cmdsID::skids_set) },
        { std::make_pair(skidsParser::cmds::skids::setThis, cmdsID::skids_setThis) },
        { std::make_pair(skidsParser::cmds::skids::setLazy, cmdsID::skids_setLazy) },
        { std::make_pair(skidsParser::cmds::skids::setThisLazy, cmdsID::skids_setThisLazy) },
        { std::make_pair(skidsParser::cmds::skids::setInteractive1, cmdsID::skids_setInteractive) },
        { std::make_pair(skidsParser::cmds::skids::setInteractive2, cmdsID::skids_setInteractive) }
    }};

    struct Command {
        std::string s_cmd;
        std::string s_name1Reg;
        std::string s_name2Reg;
        std::string s_projReg;
    };

    const static std::array<skidsFunc, 1> s_funcsArr = {{
        cmds_init,
    }};
}

#endif
