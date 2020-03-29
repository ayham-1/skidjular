#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>
#include <ctime>
#include <map>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#define LOC_DB = ".db"
#define LOC_EVENTLOG = ".log"
#define LOC_SKIDID = "skid" // used as LOC_SKIDID+SKIDNUM

/////////////// DATA CONTAINING STRUCTURES ///////////////////

struct Project {
    std::string name = "";
    std::string desc = "";
    boost::uuids::uuid uuid;
    int preferredPrior = 0;
    time_t creationDate;
    bool isDone = false;
};

struct Skid {
    std::vector<Project*> projects = {};
    time_t creationDate;
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

struct DB {
    std::map<std::string, Project> projects;
	EventLog log;
	
    time_t creationDate;
    time_t lastAccessTime;
};

#endif
