#ifndef MODULE_H
#define MODULE_H

#include <string>
#include <functional>
#include <map>

#define MODFN(name, code) \
    void name(std::string arguments) {code}
#define MODFNSIG(name) \
    void name(std::string arguments);
#define MODFNIMPL(name, code) \
    void name(std::string arguments) {code};
#define MODDISPATCHFN(name, code) \
    void name(std::string arguments) {code}
#define MODARGS(name, code) \
    struct name {code};
#define MAKEMOD(name, argsname) \
    struct name : argsname {argsname _args;};

using ModuleFn = std::function<void(std::string arguments)>;
using ModuleFnDispatcher = std::function<void(std::string arguments)>;

struct Module {
    std::string _name;
    std::string _desc;
    std::map<std::string, ModuleFn> _funcs;
    ModuleFnDispatcher _dispatcher;
};

#endif
