#ifndef MODULE_H
#define MODULE_H

#include <string>
#include <functional>
#include <map>

using ModuleFn = std::function<void(std::string arguments)>;
struct Module {
    std::string _name;
    std::string _desc;
    std::map<std::string, ModuleFn> _funcs;
};

#endif
