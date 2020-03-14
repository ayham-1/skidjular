#ifndef MODULE_INIT_H
#define MODULE_INIT_H

#include "module.h"

namespace modules {
    namespace init {
        MODARGS(
                std::string _location;
               ); 
        MODDISPATCHFNSIG(init__dispatch);

        MODFNSIG(init__create);

        MAKEMOD(DEFMOD("init", 
                    "Creates a skidjular directory in $(pwd)",
                    init__dispatch));
    };
};

#endif
