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
    std::string _name = "";
    std::string _desc = "";
    boost::uuids::uuid _uuid;
    int _preferredPrior = 0;
    time_t _creationDate;
    bool _isDone = false;
};

struct Skid {
    std::vector<Project*> _projects = {};
    time_t _creationDate;
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
    int _id = -1;
    EventType _type = EventType::None;
    std::string _mesg = "";
};

struct EventLog {
    std::vector<Event> _events;
    std::string _sha512 = "";
};

/////////////// EVENT END OF HISTORY SYSTEM STRUCTURES /////////////

struct DB {
    std::map<std::string, Project> _projects;
    EventLog _log;

    time_t _creationDate;
    time_t _lastAccessTime;
};

#endif
