#include <boost/program_options.hpp>
#include <string>
#include <vector>
#include <iostream>

int main(int argc, const char* argv[]) {
    using namespace boost::program_options;
    using namespace std;

    try {
        options_description general("General Options.");
        general.add_options()
            ("help", "Help Message")
            ("help-module", value<string>(), 
             "Module for help message")
            ;
        positional_options_description general_positional;
        general_positional.add("help", 1);
        general_positional.add("help-module", -1);

        options_description init("Init Module.");
        init.add_options()
            ("location", value<string>(), "Initial location");
        positional_options_description init_positional;
        init_positional.add("location", -1);

        options_description all("Allowed Options");
        all.add(general).add(init);
        
        variables_map vm;
        store(parse_command_line(argc, argv, all), vm);
        notify(vm);

        if (vm.count("help")) {
            auto module = vm["help-module"].as<string>();
            if (module == "init")
                std::cout << "Hello";
        } 
    }
    catch (const error &ex) {
        cerr << ex.what() << '\n';
    }

    return 0;
}
