#include "proj.h"

#include <string.h>

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>			  // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>		  // streaming operators etc.

#include "../data.h"

void proj_add(proj_args args) {
	Project proj;
	proj.name = args.action_param;

	/* Get Project description */
	std::cout << "Project description: ";
	std::cin >> proj.desc;

	/* Generate Project UUID */
	boost::uuids::uuid uuid = boost::uuids::random_generator()();
	proj.uuid				= boost::lexical_cast<std::string>(uuid);

	/* Get Priority of project */
	std::cout << "Project Priority: ";
	std::string temp;
	std::cin >> temp;
	proj.pri = stoi(temp);

	/* Creation date */
	time_t	 t		   = time(0);
	struct tm* currentTime = localtime(&t);

	proj.creationDate.day   = currentTime->tm_mday;
	proj.creationDate.month = currentTime->tm_mon;
	proj.creationDate.year  = currentTime->tm_year;

	(*args.db->projects)[proj.uuid] = proj;
	writeDB(*args.db, ".db");
	delete args.db;
}

void proj_rm(proj_args args) {}

void proj_list(proj_args args) {}

proj_mod* proj_new() {
	proj_mod* mod = new proj_mod{};
	mod->name	 = "Project Manager";
	mod->desc =
		std::string("Manages projects list with these commands:\n") +
		std::string("- skidjular proj add <Name> (Adds new project).\n") +
		std::string("- skidjular proj rm<Name> (Removes a project).\n") +
		std::string("- skidjular proj list/ls<name> (Lists commands)\n");
	return mod;
}

void proj_dispatch(const std::vector<std::string>& arguments) {
	proj_args args;
	/* Get the action type. */
	auto type_str = arguments[0];
	if (type_str == "add")
		args.type = projActType::Add;
	else if (type_str == "rm")
		args.type = projActType::Remove;
	else if (type_str == "ls" || type_str == "list")
		args.type = projActType::List;
	else {
		std::cout << "Project command action unkown!" << std::endl;
		exit(1);
	}

	/* Get action param. */
	if (arguments.size() <= 1) {
		std::cout << "No arguments passed to project action!" << std::endl;
		exit(1);
	}
	auto type_action = std::string{""};
	for (size_t i = 1; i < arguments.size(); i++) {
		type_action += arguments[i];
		type_action += " ";
	}
	type_action.pop_back();
	args.action_param = type_action;

	args.db = new DB();
	loadDB(*args.db, ".db");

	if (type_str == "add")
		proj_add(args);
	else if (type_str == "rm")
		proj_rm(args);
	else if (type_str == "list")
		proj_list(args);
}
