#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "data.h"
#include "module.h"
#include "modules/info.h"
#include "modules/init.h"
#include "modules/proj.h"

Module* get_Mod(std::string name) {
	if (name == "init") {
		return init_new();
	} else if (name == "proj") {
		return proj_new();
	} else if (name == "info") {
		return info_new();
	}
	return nullptr;
};
void dispatch_Mod(std::string mod, std::vector<std::string> args) {
	if (mod == "init") {
		init_dispatch(args);
	} else if (mod == "proj") {
		proj_dispatch(args);
	} else if (mod == "info") {
		info_dispatch(args);
	}
};

int main(int argc, const char* argv[]) {
	using namespace boost::program_options;
	using namespace std;

	try {
		options_description general("General Options");
		general.add_options()("help", "Help Message")(
			"help-module", value<string>(), "Module for help message")(
			"module", value<string>(), "Module to execute")(
			"module-args", value<vector<string>>(), "Arguments to use");
		positional_options_description general_positional;
		general_positional.add("module", 1);
		general_positional.add("module-args", 10);

		variables_map vm;
		store(command_line_parser(argc, argv)
				  .options(general)
				  .allow_unregistered()
				  .positional(general_positional)
				  .run(),
			  vm);
		notify(vm);

		if (vm.count("help")) {
			std::cout << general << "\n";
			exit(0);
		} else if (vm.count("help-module")) {
			auto name   = vm["help-module"].as<string>();
			auto module = get_Mod(name);
			if (!module) {
				std::cout << "Module not found.\n";
				exit(1);
			}
			std::cout << module->desc << "\n";
		} else if (vm.count("module")) {
			auto name = vm["module"].as<string>();
			if (!get_Mod(name)) {
				std::cout << "Module not found.\n";
				exit(1);
			}
			if (vm.count("module-args")) {
				auto args = vm["module-args"].as<vector<string>>();
				dispatch_Mod(name, args);
			} else
				dispatch_Mod(name, {""});
		} else {
			std::cout << general << "\n";
			exit(0);
		}

	} catch (const error& ex) { cerr << ex.what() << '\n'; }

	return 0;
}
