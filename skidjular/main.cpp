#include <iostream>
#include <string>
#include <memory>
#include <functional>
#include "parser/parser.h"
#include "dispatcher/dispatcher.h"
#include "tree/tree.h"

disfunc_ret testfunc(disfunc_arg) {
    std::cout << "hello world";
    return disfunc_ret_success;
}

int main(int argc, char* args[]) {
    Parser parser(argc, args);
    for (auto item : parser.get()) std::cout << item << "\n";

    Dispatcher dis(parser.get());
    auto func = std::bind(testfunc);
    dis.addArgument({"skidjular", "test"}, func);
    return 0;
}
