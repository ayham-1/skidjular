#ifndef MODULE_INIT_H
#define MODULE_INIT_H

#include <time.h>
#include <ctime>
#include <iostream>

#include "module.h"

namespace modules {
    namespace init {
        MODARGS();
        MAKEMOD(MODFNSIG(init_create);
                MODDISPATCHFN();
                DEFMOD("init",
                        "Creates a skidjular directory in $(pwd)");
                );

    };
};

#endif
