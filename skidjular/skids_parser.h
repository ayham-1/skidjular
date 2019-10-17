#ifndef SKIDS_PARSER_h
#define SKIDS_PARSER_h

#include <string>
#include <vector>
#include <array>
#include <map>
#include <functional>

#include "skidjular_funcs.h"

namespace skidsParser {
    static std::string nameRegister = "";
    static std::string dayRegister = "";
    static std::string optRegister = "";

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
}

#endif
