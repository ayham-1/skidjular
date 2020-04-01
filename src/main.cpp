#include <boost/program_options.hpp>
#include <string>
#include <vector>
#include <iostream>

#include "module.h"

#include "modules/init.h"
#include "data.h"

int main(int argc, const char* argv[]) {
    using namespace boost::program_options;
    using namespace std;
    std::map<string, Module*> lmodules;
    lmodules["init"] = new modules::init::mod;

    try {
        options_description general("General Options");
        general.add_options()
            ("help", "Help Message")
            ("help-module", value<string>(), 
             "Module for help message")
            ("module", value<string>(), "Module to execute")
            ("module-args", value<string>(), "Arguments to use")
            ;
        positional_options_description general_positional;
        general_positional.add("module", 1);
        general_positional.add("module-args", 10);

        variables_map vm;
        store(command_line_parser(argc, argv)
                .options(general).allow_unregistered()
                .positional(general_positional)
                .run(), vm);
        notify(vm);
		
		std::cout << "Hello world";
		DB db, db2;
		Project p1,p2;
		p1.name = "hello";
		p2.name = "world";
		db.projects["hello"] = p1;
		db.projects["world"] = p2;
		writeDB(db, "hello.db");
		loadDB(db2, "hello.db");
		std::cout << "\n Loading projects: ";
		std::cout << db2.projects["hello"].name;
		
        if (vm.count("help")) {
            std::cout << general << "\n";
            exit(0);
        } else if (vm.count("help-module")) {
            auto name = vm["help-module"].as<string>();
            if (lmodules.find(name) == lmodules.end()) {
                std::cout << "Module not found.\n";
                exit(1);
            }
            auto module = lmodules[name];
            std::cout << module->desc << "\n";
        }
        else if (vm.count("module")) {
            auto name = vm["module"].as<string>();

            if (lmodules.find(name) == lmodules.end()) {
                std::cout << "Module not found.\n";
                exit(1);
            }
            auto module = lmodules[name];
            
            if (vm.count("module-args")) {
				auto args = vm["module-args"].as<string>();
				module->dispatch(args);
			} else	module->dispatch("");
        }
        else {
            std::cout << general << "\n";
            exit(0);
        }


    }
    catch (const error &ex) {
        cerr << ex.what() << '\n';
    }

    return 0;
}
