#include "init.h"

#include "../data.h"

void init_create(init_args arg) {
	std::cout << "Creating database in current directory." << std::endl;
	DB		   db;
	time_t	 t		   = time(0);
	struct tm* currentTime = localtime(&t);

	db.creationDate.day		= currentTime->tm_mday;
	db.creationDate.month   = currentTime->tm_mon;
	db.creationDate.year	= currentTime->tm_year + 1900;
	db.lastAccessTime.day   = currentTime->tm_mday;
	db.lastAccessTime.month = currentTime->tm_mon;
	db.lastAccessTime.year  = currentTime->tm_year + 1900;

	// Mandatory stuff to stop segmantion fault due to
	// pointers unintialized.
	db.projects	= new std::map<std::string, Project>();
	db.log.entries = new std::list<Entry>();

	logEntry("Creating database.", EntryType::Creation);
	writeDB(db, ".db");
}

void init_dispatch(const std::vector<std::string>& arguments) {
	init_args arg;
	init_create(arg);
}

init_mod* init_new() {
	init_mod* mod = new init_mod{};
	mod->name	 = "Init";
	mod->desc	 = "Creates skidjular directory in $(pwd)";
	return mod;
}
