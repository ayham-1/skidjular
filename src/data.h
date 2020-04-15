#ifndef DATA_H
#define DATA_H
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>

#include "json.hpp"
using nlohmann::json;

#define LOC_DB ".db"
#define LOC_LOG ".log"
#define LOC_SKIDID "skid" // used as LOC_SKIDID+SKIDNUM

/////////////// DATA CONTAINING STRUCTURES ///////////////////

struct Date {
	int day	= 0;
	int month  = 0; // 0-11
	int year   = 0; // + 1900 for currentyear
	int hour   = 0;
	int minute = 0;
	int second = 0;
};

struct Project {
	std::string name = "";
	std::string desc = "";
	std::string uuid;
	int			pri = 0;
	Date		creationDate;
	Date		doneDate;
	bool		isDone = false;
};

struct Skid {
	std::vector<Project>* projects = {};
	Date				  creationDate;
};

/////////////// END OF DATA CONTAINING STRUCTURES ////////////

/////////////// EVENT HISTORY SYSTEM STRUCTURES ////////////////////

enum EntryType { Access = 0, Creation = 1, Modification = 2, None = -1 };

struct Entry {
	EntryType   type	  = EntryType::None;
	std::string mesg	  = "";
	float		timerTime = 0.0f;
	Date		creationDate;
};

struct Log {
	std::list<Entry>* entries = nullptr;
};

/////////////// EVENT END OF HISTORY SYSTEM STRUCTURES /////////////

// Main Database that represents the skidjular directory.
struct DB {
	std::map<std::string, Project>* projects;
	std::vector<Skid>				skids;
	Log								log;

	Date creationDate;
	Date lastAccessTime;
};

////////////// Utilities for the Database structure ////////////////

void writeDB(DB db, const std::string& dest);
void loadDB(DB& db, const std::string& src);

////////////// End Utilities for the Database structure ////////////

#endif
