#include "dispatcher.h"

Dispatcher::Dispatcher(std::vector<std::string> args) {
    this->m_parsedArgs = args;
}
Dispatcher::~Dispatcher(void) {}

auto Dispatcher::dispatch()->disfunc_ret {
    return disfunc_ret_fail;
}

auto Dispatcher::addArgument(std::vector<std::string> argument, disfunc func)->void {
}
