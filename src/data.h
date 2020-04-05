#ifndef DATA_H
#define DATA_H

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "json.hpp"
using nlohmann::json;

#define LOC_DB		 = ".db"
#define LOC_EVENTLOG = ".log"
#define LOC_SKIDID	 = "skid" // used as LOC_SKIDID+SKIDNUM

/////////////// DATA CONTAINING STRUCTURES ///////////////////

struct Date {
  int day	= 0;
  int month = 0; // 0-11
  int year	= 0; // + 1900 for currentyear
};

struct Project {
  std::string name = "";
  std::string desc = "";
  std::string uuid;
  int		  pri = 0;
  Date		  creationDate;
  Date		  doneDate;
  bool		  isDone = false;
};

struct Skid {
  std::vector<Project>* projects = {};
  Date					creationDate;
};

/////////////// END OF DATA CONTAINING STRUCTURES ////////////

/////////////// EVENT HISTORY SYSTEM STRUCTURES ////////////////////

enum EventType { Access = 0, Creation = 1, Modification = 2, None = -1 };

struct Event {
  int		  id   = -1;
  EventType	  type = EventType::None;
  std::string mesg = "";
};

struct EventLog {
  std::vector<Event>* events;
  std::string		  sha512 = "";
};

/////////////// EVENT END OF HISTORY SYSTEM STRUCTURES /////////////

// Main Database that represents the skidjular directory.
struct DB {
  std::map<std::string, Project>* projects;
  std::vector<Skid>				  skids;
  EventLog						  log;

  Date creationDate;
  Date lastAccessTime;
};

////////////// Utilities for the Database structure ////////////////

void writeDB(DB db, const std::string& dest);
void loadDB(DB& db, const std::string& src);

////////////// End Utilities for the Database structure ////////////

#endif
