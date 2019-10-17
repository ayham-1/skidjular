#ifndef SKIDS_PARSER_h
#define SKIDS_PARSER_h

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

    const static std::array<std::pair<std::string, skidsFunc>, 17> s_funcMap = {{
        { std::make_pair(skidsParser::cmds::init, cmds_init) },
        { std::make_pair(skidsParser::cmds::history, cmds_history) },
        { std::make_pair(skidsParser::cmds::info, cmds_info) },
        { std::make_pair(skidsParser::cmds::proj::add, cmds_proj_add) },
        { std::make_pair(skidsParser::cmds::proj::rm, cmds_proj_rm) },
        { std::make_pair(skidsParser::cmds::proj::list1, cmds_proj_list) },
        { std::make_pair(skidsParser::cmds::proj::list2, cmds_proj_list) },
        { std::make_pair(skidsParser::cmds::skids::init, cmds_skids_init) },
        { std::make_pair(skidsParser::cmds::skids::initNow, cmds_skids_initNow) },
        { std::make_pair(skidsParser::cmds::skids::now, cmds_skids_now) },
        { std::make_pair(skidsParser::cmds::skids::set, cmds_skids_set) },
        { std::make_pair(skidsParser::cmds::skids::setThis, cmds_skids_setThis) },
        { std::make_pair(skidsParser::cmds::skids::setLazy, cmds_skids_setLazy) },
        { std::make_pair(skidsParser::cmds::skids::setThisLazy, cmds_skids_setThisLazy) },
        { std::make_pair(skidsParser::cmds::skids::setInteractive1, cmds_skids_setInteractive) },
        { std::make_pair(skidsParser::cmds::skids::setInteractive2, cmds_skids_setInteractive) }
        }};
}

#endif
