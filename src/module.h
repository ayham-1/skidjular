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
    void mod::dispatch(std::string arguments) {code}
#define MODDISPATCHFN() \
    void dispatch(std::string arguments) override; 

#define MODARGS(code) \
    struct args {code}
#define MAKEMOD(code) \
    struct mod : args, Module {code}
#define DEFMOD(name_, desc_) \
    mod() { \
        this->name = name_; \
        this->desc = desc_; \
    } \

using ModuleFn = std::function<void(std::string arguments)>;
using ModuleFnDispatcher = std::function<void(std::string arguments)>;

struct Module {
    std::string name;
    std::string desc;
    std::map<std::string, ModuleFn> funcs;
    MODDISPATCHFNSIG();
};

#endif
