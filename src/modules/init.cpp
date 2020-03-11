#include "init.h"
#include <iostream> 

namespace modules {
    namespace init {
        MODFNIMPL(init_create, {
                std::cout << "CREATE";
                });

        MODDISPATCHFNIMPL(init__dispatch, {
                std::cout << arguments;
                });
    }
};
