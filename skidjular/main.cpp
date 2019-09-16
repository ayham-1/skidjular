#include <iostream>
#include <string>
#include <memory>
#include "parser/parser.h"
#include "dispatcher/dispatcher.h"
#include "tree/tree.h"

int main(int argc, char** args) {
    Tree<int> test;
    test.addNode("", "root", 5);
    test.addNode("root",  "test1", 1);
    test.addNode("root", "test3", 3);
    test.addNode("test3", "test2", 2);

    std::cout << test.searchTree(test.getTree(), "test2")->s_data;

    test.remNode("test3");
    test.printTree(test.getTree());
    std::cout << test.searchTree(test.getTree(), "test2")->s_data;

    return 0;
}
