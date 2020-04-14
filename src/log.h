#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <iostream>

#include "data.h"
#include "timer.h"

static Log s_log;

void addEntry(const std::string& msg, EntryType type);
void writeLog(const std::string& loc,
			  bool				 append = true /* false == overwrite */);
void printLog(const std::string& loc,
			  int				 entries = 0 /* 0 == None, -1 == All */);

#endif
