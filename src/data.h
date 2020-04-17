#ifndef DATA_H
#define DATA_H

#include <sys/stat.h>
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

////// DATA STRUCTURES

struct Date {
	int day	   = 0;
	int month  = 0; // 0-11
	int year   = 0; // + 1900 for currentyear
	int hour   = 0;
	int minute = 0;
	int second = 0;

	bool operator==(const Date& other) {
		if (day == other.day)
			if (month == other.month)
				if (year == other.year)
					if (hour == other.hour)
						if (minute == other.minute)
							if (second == other.minute)
								return true;
		return false;
	}
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
	Project* project = nullptr;
	Date	 creationDate;
	Date	 date;
};

//////// EVENT HISTORY

enum EntryType { Access = 0, Creation = 1, Modification = 2, None = -1 };

struct Entry {
	EntryType	type	  = EntryType::None;
	std::string mesg	  = "";
	float		timerTime = 0.0f;
	Date		creationDate;
};

struct Log {
	std::list<Entry>* entries = nullptr;
};

// Main Database that represents the skidjular directory.
struct DB {
	std::map<std::string, Project>* projects;
	std::vector<Skid>				skids;
	Log								log;
	int								lastSkidID = 1;

	Date creationDate;
	Date lastAccessTime;
	;
};

//////// UTILITIES

void writeDB(DB db, const std::string& dest);
void loadDB(DB& db, const std::string& src);

void writeSkid(Skid skid, int skidNum);
void loadSkid(Skid& skid, int skidNum);

Date get_today();
Date addDays_date(Date initial, int);

bool is_empty(std::ifstream& pFile);
bool is_path_exist(const std::string& s);

Project* find_proj(DB& db, std::string name);

#endif
