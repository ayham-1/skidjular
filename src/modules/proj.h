#ifndef MODULE_PROJ_H
#define MODULE_PROJ_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "data.h"
#include "module.h"

enum projActType { Add, Remove, List };
struct proj_args {
	projActType type;
	std::string action_param;

	DB* db;
};
struct proj_mod : proj_args, Module {};

proj_mod* proj_new();
void	  proj_add(proj_args args);
void	  proj_rm(proj_args args);
void	  proj_list(proj_args args);
void	  proj_dispatch(const std::vector<std::string>& arguments);

#endif
