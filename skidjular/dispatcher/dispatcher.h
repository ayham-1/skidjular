#pragma once

#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>

#define disfunc_ret bool
#define disfunc_ret_fail false
#define disfunc_ret_success true
#define disfunc_arg 
//#define disfunc std::function<disfunc_ret(disfunc_arg)>
using disfunc = std::function<disfunc_ret(disfunc_arg)>;

class Dispatcher {
    public:
        Dispatcher(std::vector<std::string> args);
        ~Dispatcher(void);

        auto dispatch()->disfunc_ret;

        auto addArgument(std::vector<std::string> argument, disfunc func)->void;
    private:
        std::vector<std::string> m_parsedArgs;
        std::map<std::vector<std::string>, std::string> m_argumentArr;
};
#endif
