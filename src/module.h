#ifndef MODULE_H
#define MODULE_H

#include <functional>
#include <map>
#include <string>

using ModuleFn			 = std::function<void(std::string arguments)>;
using ModuleFnDispatcher = std::function<void(std::string arguments)>;

struct Module {
  std::string					  name;
  std::string					  desc;
  std::map<std::string, ModuleFn> funcs;
};

#endif
