#ifndef MODULE_INIT_H
#define MODULE_INIT_H

#include "module.h"

namespace modules {
    namespace init {
        MODARGS(
                std::string _location;
               ); 
        MAKEMOD(MODFNSIG(init__create);
                MODDISPATCHFN();
                DEFMOD("init", 
                        "Creates a skidjular directory in $(pwd)");
                );

    };
};

#endif
