#include "proj.h"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>			  // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>		  // streaming operators etc.

void proj_add(proj_args args) {
	logEntry("Creating project with name: " + args.action_param,
			 EntryType::Creation);
	Project proj;
	proj.name = args.action_param;

	/* Get Project description */
	std::cout << "Project description: ";
	std::getline(std::cin, proj.desc);

	/* Generate Project UUID */
	boost::uuids::uuid uuid = boost::uuids::random_generator()();
	proj.uuid				= boost::lexical_cast<std::string>(uuid);

	/* Get Priority of project */
	std::cout << "Project Priority: ";
	std::string temp;
	std::getline(std::cin, temp);
	proj.pri = stoi(temp);

	/* Creation date */
	proj.creationDate = get_today();

	(*args.db->projects)[proj.uuid] = proj;
	writeDB(*args.db, LOC_DB);
	delete args.db;
}

void proj_rm(proj_args args) {
	logEntry("Removing project with name: " + args.action_param,
			 EntryType::Modification);
	/* Delete project from database */
	for (auto it = args.db->projects->begin(); it != args.db->projects->end();
		 it++) {
		if (it->second.name == args.action_param) {
			args.db->projects->erase(it);
			writeDB(*args.db, LOC_DB);
			logEntry("Deleted project successfully!", EntryType::Modification);
			exit(0);
		}
	}
	std::cout << "Project name not found!" << std::endl;
	exit(1);
}

void proj_list(proj_args args) {
	int counter = 0;
	for (auto project: *(args.db->projects)) {
		std::stringstream header;
		header << "Project #" << ++counter
			   << "-----------------------------------";
		std::cout << header.str() << std::endl;
		std::cout << "Project name: " << project.second.name << std::endl;
		std::cout << "Project description: " << project.second.desc
				  << std::endl;
		std::cout << "Project UUID: " << project.second.uuid << std::endl;
		std::cout << "Project PRI: " << project.second.pri << std::endl;
		std::cout << "Creation Date: " << project.second.creationDate.day << "/"
				  << project.second.creationDate.month << "/"
				  << project.second.creationDate.year << std::endl;
		std::cout << "Done Date: " << project.second.doneDate.day << "/"
				  << project.second.doneDate.month << "/"
				  << project.second.doneDate.year << std::endl;
		std::cout << "Is done: " << project.second.isDone << std::endl;
		for (size_t i = 0; i < header.str().size(); i++) std::cout << "-";
		std::cout << std::endl;
	}
}

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
	if (type_str == "add" || type_str == "rm") {
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
	} else
		args.action_param = "";

	/* Load database */
	args.db = new DB();
	loadDB(*args.db, LOC_DB);

	if (type_str == "add")
		proj_add(args);
	else if (type_str == "rm")
		proj_rm(args);
	else if (type_str == "list" || type_str == "ls")
		proj_list(args);
}
