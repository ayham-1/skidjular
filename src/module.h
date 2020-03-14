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
    void name(std::string arguments) {code}

#define MODDISPATCHFN(name, code) \
    void name(std::string arguments) {code}
#define MODDISPATCHFNSIG(name) \
    void name(std::string arguments); 
#define MODDISPATCHFNIMPL(name, code) \
    void name(std::string arguments) {code}

#define MODARGS(code) \
    struct _args {code}
#define MAKEMOD(code) \
    struct _mod : _args, Module {code}
#define DEFMOD(name, desc, dispatcher) \
    _mod() { \
        this->_name = name; \
        this->_desc = desc; \
        this->_dispatcher = dispatcher; \
    } \

using ModuleFn = std::function<void(std::string arguments)>;
using ModuleFnDispatcher = std::function<void(std::string arguments)>;

struct Module {
    std::string _name;
    std::string _desc;
    std::map<std::string, ModuleFn> _funcs;
    ModuleFnDispatcher _dispatcher;
};

#endif
