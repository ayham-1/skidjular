#include "skids.h"

void skids_init(skids_args args) {
	logEntry("Creating new skids, skids_init", EntryType::Creation);

	/* Check first day of process */
	Date firstDate;
	if (is_path_exist(LOC_SKIDID + std::to_string(args.db->lastSkidID))) {
		Skid skid;
		loadSkid(skid, args.db->lastSkidID);
		firstDate = skid.date;
	} else {
		/* Today is the first day */
		firstDate = get_today();
	}

	/* Create skids */
	for (size_t i = 1; i <= 7; i++) {
		Skid skid;
		skid.creationDate = get_today();
		skid.date		  = firstDate;
		firstDate		  = addDays_date(firstDate, 1);
		writeSkid(skid, args.db->lastSkidID++);
	}

	/* Update database with right lastSkidID */
	writeDB(*args.db, LOC_DB);
}

void skids_init_now(skids_args args) {
	logEntry("Creating new skids, skids_init_now", EntryType::Creation);

	int skid_id = 0;
	/* Load all skids */
	if (is_path_exist(LOC_SKIDID + std::to_string(args.db->lastSkidID))) {
		/* Load all skids */
		for (size_t i = 1; i <= args.db->lastSkidID; i++) {
			Skid skid;
			loadSkid(skid, i);
			args.db->skids.push_back(skid);
		}

		/* Get today's skidID */
		for (size_t i = 0; i < args.db->skids.size(); i++) {
			if (args.db->skids[i].date == get_today()) {
				skid_id = i;
				break;
			}
		}

		/* Set skid_id to last id */
		skid_id = args.db->lastSkidID;
	} else {
		/* ID == 0 */
		skid_id = 0;
	}

	/* Create skids */
	auto firstDate = get_today();
	for (size_t i = 1; i <= 7; i++) {
		Skid skid;
		skid.creationDate = get_today();
		skid.date		  = firstDate;
		firstDate		  = addDays_date(firstDate, 1);
		writeSkid(skid, skid_id++);
	}

	args.db->lastSkidID = skid_id;
	writeDB(*args.db, LOC_DB);
}

void skids_now(skids_args args) {
	logEntry("Accessing today's skid, skids_now", EntryType::Access);
	/* Load all skids */
	for (size_t i = 1; i <= args.db->lastSkidID; i++) {
		Skid skid;
		loadSkid(skid, i);
		args.db->skids.push_back(skid);
	}

	/* Get today's skidID */
	Skid* skid = nullptr;
	for (size_t i = 0; i < args.db->skids.size(); i++) {
		if (args.db->skids[i].date == get_today()) {
			skid = &(args.db->skids[i]);
			break;
		}
	}

	if (!skid) {
		std::cout << "Did not find today's skid." << std::endl;
		exit(1);
	}

	if (skid->project->name == "") {
		std::cout << "Today's project is not set." << std::endl;
		exit(1);
	}

	std::cout << "Project of today is " << skid->project->name << std::endl;
	exit(0);
}

void skids_this(skids_args args) {
	logEntry("Accessing week's skid, skids_this", EntryType::Access);
	/* Load all skids */
	for (size_t i = 1; i <= args.db->lastSkidID; i++) {
		Skid skid;
		loadSkid(skid, i);
		args.db->skids.push_back(skid);
	}

	/* Get week's skidID */
	std::vector<Skid*> skids;
	for (size_t i = 0; i < args.db->skids.size(); i++) {
		if (args.db->skids[i].date == get_today()) {
			for (size_t j = i; j < args.db->skids.size(); j++)
				skids.push_back(&(args.db->skids[j]));
			break;
		}
	}

	for (auto skid: skids) {
		std::cout << skid->date.year << "/" << skid->date.month << "/"
				  << skid->date.day;
		if (skid->project->name == "")
			std::cout << ": Project unset." << std::endl;
		else
			std::cout << ": " << skid->project->name << std::endl;
	}
}
void skids_set_this(skids_args args) {}
void skids_set_this_lazy(skids_args args) {}
void skids_set_lazy(skids_args args) {}
void skids_set_day(skids_args args) {}
void skids_set_interactive(skids_args args) {}

skids_mod* skids_new() {
	skids_mod* mod = new skids_mod();
	mod->name	   = "skids Manager";
	mod->desc =
		std::string("Manages the skids data with these commands:\n") +
		std::string(
			"- skidjular skids init (Creates the next uncreated week)\n") +
		std::string("- skidjular skids init now (Force creates this week)\n") +
		std::string("- skidjular skids this (Outputs this week's projects)\n") +
		std::string("- skidjular skids now (Outputs today's project)\n") +
		std::string("- skidjular skids set this <day> <proj_name> (Set this "
					"week's <day> to <proj>)\n") +
		std::string("- skidjular skids set <day> <proj_name> (Sets next unset "
					"<day> to <proj>\n") +
		std::string("- skidjular skids set this lazy (Force sets this week's "
					"projects automatically)\n") +
		std::string("- skidjular skids set lazy (Sets next unset week's "
					"projects automatically)\n") +
		std::string("- skidjular skids i/interactive (Sets next unset week's "
					"projects interactively)\n");
	return mod;
}

void skids_dispatch(const std::vector<std::string>& arguments) {
	skids_args args;
	void (*func)(skids_args) = nullptr;

	/* Get the action type and action param. */
	size_t param_offset = 0;
	auto   type_str		= arguments[0];
	if (type_str == "init") {
		if (arguments.size() > 1) {
			if (arguments[1] == "now") {
				args.type	 = skidsActType::init_now;
				param_offset = 2;
				func		 = skids_init_now;
				goto afterActionGet;
			}
		}
		args.type = skidsActType::init;
		func	  = skids_init;
		goto afterActionGet;
	} else if (type_str == "now") {
		args.type	 = skidsActType::now;
		param_offset = 1;
		func		 = skids_now;
		goto afterActionGet;
	} else if (type_str == "this") {
		args.type	 = skidsActType::this_;
		param_offset = 1;
		func		 = skids_this;
		goto afterActionGet;
	} else if (type_str == "set") {
		if (arguments.size() > 1) {
			auto type_str2 = arguments[1];
			if (type_str2 == "this") {
				if (arguments.size() > 2) {
					auto type_str3 = arguments[2];
					if (type_str3 == "lazy") {
						args.type	 = skidsActType::set_this_lazy;
						param_offset = 3;
						func		 = skids_set_this_lazy;
						goto afterActionGet;
					}
					args.type = skidsActType::set_this;
					func	  = skids_set_this;
					goto afterActionGet;
				}
			} else if (type_str2 == "lazy") {
				args.type	 = skidsActType::set_lazy;
				param_offset = 2;
				func		 = skids_set_lazy;
				goto afterActionGet;
			} else if (type_str2 == "interactive" || type_str2 == "i") {
				args.type	 = skidsActType::set_interactive;
				param_offset = 2;
				func		 = skids_set_lazy;
				goto afterActionGet;
			} else if (arguments.size() >= 3) {
				args.type	 = skidsActType::set_day;
				param_offset = 4;
				func		 = skids_set_day;
				goto afterActionGet;
			}
		}
	}
	std::cout << "Inavlid number of arguments passed to skids!" << std::endl;
	exit(1);

afterActionGet:
	/* Retrieve action parameter. */
	if (param_offset >= arguments.size()) {
		args.action_param = {};
	} else {
		for (size_t i = param_offset; i < arguments.size(); i++) {
			args.action_param.push_back(arguments[i]);
		}
	}

	/* Load database */
	args.db = new DB();
	loadDB(*args.db, LOC_DB);

	/* Finally, dispatch function. Bye bye! */
	assert(func);
	func(args);
}
