#ifndef DATA_H

#define DATA_H

#include <string>
#include <vector>
#include <map>

#include <fstream>

#include "json.hpp"
using nlohmann::json;

#define LOC_DB = ".db"
#define LOC_EVENTLOG = ".log"
#define LOC_SKIDID = "skid" // used as LOC_SKIDID+SKIDNUM

/////////////// DATA CONTAINING STRUCTURES ///////////////////

struct Date {
	int day = 0;
	int month = 0;
	int year = 0;
};

struct Project {
    std::string name = "";
    std::string desc = "";
	std::string uuid;
    int pri = 0;
    Date creationDate;
	Date doneDate;
    bool isDone = false;
};

struct Skid {
    std::vector<Project*> projects = {};
    Date creationDate;
};

/////////////// END OF DATA CONTAINING STRUCTURES ////////////


/////////////// EVENT HISTORY SYSTEM STRUCTURES ////////////////////

enum EventType {
    Access = 0,
    Creation = 1,
    Modification = 2,
    None = -1
};

struct Event {
    int id = -1;
    EventType type = EventType::None;
    std::string mesg = "";
};

struct EventLog {
    std::vector<Event> events;
    std::string sha512 = "";
};

/////////////// EVENT END OF HISTORY SYSTEM STRUCTURES /////////////

// Main Database that represents the skidjular directory.
struct DB {
    std::map<std::string, Project> projects;
	EventLog log;
	
    Date creationDate;
    Date lastAccessTime;
};

////////////// Helping functions for JSON  /////////////////////////

void to_json(json& j, const Date& date) {
	j = json{
			 {"day", date.day},
			 {"month", date.day},
			 {"year", date.year}
	};
}

void from_json(const json& j, Date& date) {
	j.at("day").get_to(date.day);
	j.at("month").get_to(date.month);
	j.at("year").get_to(date.year);
}

void to_json(json& j, const Project& proj) {
	j = json{
			 {"name", proj.name},
			 {"desc", proj.desc},
			 {"uuid", proj.uuid},
			 {"pri", proj.pri},
			 {"creationDate", proj.creationDate},
			 {"doneDate", proj.doneDate},
			 {"isDone", proj.isDone}
	};
}

void from_json(const json& j, Project& proj) {
	j.at("name").get_to(proj.name);
	j.at("desc").get_to(proj.desc);
	j.at("uuid").get_to(proj.uuid);
	j.at("pri").get_to(proj.pri);
	j.at("creationDate").get_to(proj.creationDate);
	j.at("doneDate").get_to(proj.doneDate);
	j.at("isDone").get_to(proj.isDone);
}

void to_json(json& j, const DB& db) {
	j = json{
			 {"projects", db.projects},
			 {"creationDate", db.creationDate},
			 {"lastAccessTime", db.lastAccessTime}
	};
}
void from_json(const json& j, DB& db) {
	j.at("projects").get_to(db.projects);
	j.at("creationDate").get_to(db.creationDate);
	j.at("lastAccessTime").get_to(db.lastAccessTime);
}

////////////// End Helping functions for JSON  /////////////////////

////////////// Utilities for the Database structure ////////////////

void writeDB(DB db, const std::string &dest) {
	try {
		std::ofstream f(dest);
		json j = db;
		f << j;
	} catch (...) {
		std::cout << "Failed writing database to: " << dest << std::endl;
	}
}

void loadDB(DB &db, const std::string &src) {
	try {
		std::ifstream f(src);
		json j;
		f >> j;
		db = j;
	} catch (const std::exception& ex) {
		std::cout << "Failed loading database from: " << src << std::endl;
		std::cout << "Error: " << ex.what() << std::endl;
	}
}

////////////// End Utilities for the Database structure ////////////

#endif
