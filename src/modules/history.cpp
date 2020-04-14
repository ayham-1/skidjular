#include "history.h"

void history_print(history_args args) {
	printLog(LOC_LOG, args.entries_num);
	std::cout << "hel";
}

history_mod* history_new() {
	history_mod* mod = new history_mod();
	mod->name		 = "History";
	mod->desc		 = "Shows n entries, passed into the module";
	return mod;
}

void history_dispatch(const std::vector<std::string>& argument) {
	history_args args;
	if (argument.size() == 0)
		args.entries_num = 0;
	else if (argument.size() == 1)
		args.entries_num = stoi(argument[0]);
	else if (argument.size() >= 1) {
		std::cout << "Too much arguments are passed!" << std::endl;
		exit(1);
	}

	history_print(args);
}
