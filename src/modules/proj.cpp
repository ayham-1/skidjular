#include "proj.h"

#include <string.h>

#include "../data.h"

void proj_add(proj_args args) {}

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

	/* Get action type. */
	auto type_action = std::string{""};
	for (size_t i = 1; i < arguments.size(); i++) {
		type_action += arguments[i];
		type_action += " ";
	}
	type_action.pop_back();
	args.action_param = type_action;

	if (type_str == "add")
		proj_add(args);
	else if (type_str == "rm")
		proj_rm(args);
	else if (type_str == "list")
		proj_list(args);

	args.db = new DB();
	loadDB(*args.db, ".db");

	std::cout << "Action: " << type_str << std::endl
			  << "Args: " << type_action << std::endl;
}
