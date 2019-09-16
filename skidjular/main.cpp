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

    test.printTree(test.getTree());
    test.remNode("test3");
    std::cout << "\n";
    test.printTree(test.getTree());

    return 0;
}
