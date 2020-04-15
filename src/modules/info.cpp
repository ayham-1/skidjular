#include "info.h"

void info_print(info_args args) {
	std::cout << "-----------------------" << std::endl;
	std::cout << "Creation Date: " << args.db->creationDate.day << "/"
			  << args.db->creationDate.month << "/"
			  << args.db->creationDate.year << std::endl;
	std::cout << "Last Access Date: " << args.db->creationDate.day << "/"
			  << args.db->creationDate.month << "/"
			  << args.db->creationDate.year << std::endl;
	std::cout << "Projects Number: " << args.db->projects->size() << std::endl;
	std::cout << "-----------------------" << std::endl;
}

info_mod* info_new() {
	info_mod* mod = new info_mod{};
	mod->name	 = "Info";
	mod->desc	 = "Shows information about the skids databse";
	return mod;
}

void info_dispatch(const std::vector<std::string>& arguments) {
	info_args args;
	args.db = new DB();
	loadDB(*args.db, LOC_DB);
	info_print(args);
}
