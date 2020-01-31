#include <boost/program_options.hpp>
#include <string>
#include <vector>
#include <iostream>

#include "module.h"

int main(int argc, const char* argv[]) {
    using namespace boost::program_options;
    using namespace std;
    std::map<string, Module> modules;

    try {
        options_description general("General Options.");
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

        if (vm.count("help")) {
            if (vm.count("help-module")) {
                auto name = vm["help-module"].as<string>();
                if (modules.find(name) == modules.end()) {
                    std::cout << "Module not found.\n";
                    exit(1);
                }
                auto module = modules[name];
                std::cout << module._desc << "\n";
            }
            else std::cout << general << "\n";
            exit(0);
        } 

        if (vm.count("module")) {
            auto name = vm["module"].as<string>();

            if (modules.find(name) == modules.end()) {
                std::cout << "Module not found.\n";
                exit(1);
            }

            auto module = modules[name];
            auto args = string{""};

            if (vm.count("module-args"))
                args = vm["module-args"].as<string>();

            module._dispatcher(args);
        }
    }
    catch (const error &ex) {
        cerr << ex.what() << '\n';
    }

    return 0;
}
