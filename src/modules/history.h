#ifndef MODULE_HISTORY_H
#define MODULE_HISTORY_H

#include <iostream>
#include <string>

#include "data.h"
#include "log.h"
#include "module.h"

struct history_args {
	int entries_num = 0;
};

struct history_mod : history_args, Module {};

history_mod* history_new();
void		 history_print(history_args args);
void		 history_dispatch(const std::vector<std::string>& arguments);

#endif
