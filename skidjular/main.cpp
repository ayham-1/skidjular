#include <iostream>
#include <string>
#include "skids_parser.h"

int main(int argc, char *argv[]) {
    auto args = skidsParser::buildCmd(argc, argv);
    std::cout << args.s_cmd << std::endl;
    skidsParser::dispatch(args);
  return 0;
}
