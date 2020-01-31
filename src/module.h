#ifndef MODULE_H
#define MODULE_H

#include <string>
#include <functional>
#include <map>

#define MODFN(name, code) \
    void name(std::string arguments) {code}
#define MODDISPATCHFN(name, code) \
    void name(std::string arguments) {code}

using ModuleFn = std::function<void(std::string arguments)>;
using ModuleFnDispatcher = std::function<void(std::string arguments)>;

struct Module {
    std::string _name;
    std::string _desc;
    std::map<std::string, ModuleFn> _funcs;
    ModuleFnDispatcher _dispatcher;
};

#endif
