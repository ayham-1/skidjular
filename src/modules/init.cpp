#include "init.h"
#include <iostream> 

namespace modules {
    namespace init {
        MODFNIMPL(init_create, {
				std::cout << "Creating database in current directory."
						  << std::endl;
                });

        MODDISPATCHFNIMPL({
				init_create(arguments);
                });
    }
};
