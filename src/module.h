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

#define MODDISPATCHFNSIG() \
    virtual void dispatch(std::string arguments) = 0;
#define MODDISPATCHFNIMPL(code) \
    void _mod::dispatch(std::string arguments) {code}
#define MODDISPATCHFN() \
    void dispatch(std::string arguments) override; 

#define MODARGS(code) \
    struct _args {code}
#define MAKEMOD(code) \
    struct _mod : _args, Module {code}
#define DEFMOD(name, desc) \
    _mod() { \
        this->_name = name; \
        this->_desc = desc; \
    } \

using ModuleFn = std::function<void(std::string arguments)>;
using ModuleFnDispatcher = std::function<void(std::string arguments)>;

struct Module {
    std::string _name;
    std::string _desc;
    std::map<std::string, ModuleFn> _funcs;
    MODDISPATCHFNSIG();
};

#endif
