#ifndef MODULE_INIT_H
#define MODULE_INIT_H

#include <time.h>
#include <ctime>
#include <iostream>
#include <vector>

#include "../data.h"
#include "../log.h"
#include "module.h"

struct init_args {};
struct init_mod : init_args, Module {};

init_mod* init_new();
void	  init_create(init_args arg);
void	  init_dispatch(const std::vector<std::string>& arguments);

#endif
