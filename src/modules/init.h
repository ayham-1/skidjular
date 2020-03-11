#ifndef MODULE_INIT_H
#define MODULE_INIT_H

#include "module.h"

namespace modules {
    namespace init {
        MODARGS(
                std::string _location;
               ); 
        MAKEMOD();

        MODDISPATCHFNSIG(init__dispatch);

        MODFNSIG(init__create);
    };
};

#endif
