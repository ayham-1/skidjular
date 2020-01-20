#include <iostream>
#include <string>
#include "skids_parser.h"

int main(int argc, char *argv[]) {
    std::cout << "Hello";
    auto args = skidsParser::buildCmd(argc, argv);
<<<<<<< Updated upstream
    std::cout << args.s_cmd << std::endl;
    skidsParser::dispatch(args);
=======
    //skidsParser::dispatch(args);
>>>>>>> Stashed changes
  return 0;
}
