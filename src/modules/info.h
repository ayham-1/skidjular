#ifndef MODULE_INFO_H
#define MODULE_INFO_H

#include <iostream>
#include <string>

#include "data.h"
#include "module.h"

struct info_args {
	DB* db;
};

struct info_mod : info_args, Module {};

info_mod* info_new();
void	  info_print(info_args args);
void	  info_dispatch(const std::vector<std::string>& arguments);
#endif
