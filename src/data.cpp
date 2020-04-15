#include "data.h"
#include "log.h"

void to_json(json& j, const Date& date) {
	j = json{{"day", date.day}, {"month", date.day}, {"year", date.year}};
}
void from_json(const json& j, Date& date) {
	j.at("day").get_to(date.day);
	j.at("month").get_to(date.month);
	j.at("year").get_to(date.year);
}
void to_json(json& j, const Project& proj) {
	j = json{{"name", proj.name},
			 {"desc", proj.desc},
			 {"uuid", proj.uuid},
			 {"pri", proj.pri},
			 {"creationDate", proj.creationDate},
			 {"doneDate", proj.doneDate},
			 {"isDone", proj.isDone}};
}
void from_json(const json& j, Project& proj) {
	j.at("name").get_to(proj.name);
	j.at("desc").get_to(proj.desc);
	j.at("uuid").get_to(proj.uuid);
	j.at("pri").get_to(proj.pri);
	j.at("creationDate").get_to(proj.creationDate);
	j.at("doneDate").get_to(proj.doneDate);
	j.at("isDone").get_to(proj.isDone);
}
void to_json(json& j, const Skid& skid) {
	Project projects;
	if (skid.projects != nullptr) {
		projects = *skid.projects;
	}
	j = json{
		{"projects", projects},
		{"creationDate", skid.creationDate},
	};
}
void from_json(const json& j, Skid& skid) {
	skid.projects = new Project();
	j.at("projects").get_to(*skid.projects);
	j.at("creationDate").get_to(skid.creationDate);
}
void to_json(json& j, const DB& db) {
	std::map<std::string, Project> projects;
	if (db.projects != nullptr) {
		projects = *db.projects;
	};
	j = json{{"projects", projects},
			 {"creationDate", db.creationDate},
			 {"lastAccessTime", db.lastAccessTime}};
}
void from_json(const json& j, DB& db) {
	db.projects = new std::map<std::string, Project>();
	j.at("projects").get_to(*db.projects);
	j.at("creationDate").get_to(db.creationDate);
	j.at("lastAccessTime").get_to(db.lastAccessTime);
}

void writeDB(DB db, const std::string& dest) {
	try {
		logEntry("Writing Database...", EntryType::Modification);
		std::ofstream f(dest);
		json		  j = db;
		f << j;
	} catch (std::exception& ex) {
		std::cout << "Failed writing database to: " << dest << std::endl;
		std::cout << "Error: " << ex.what() << std::endl;
	}
}
bool is_empty(std::ifstream& pFile) {
	return pFile.peek() == std::ifstream::traits_type::eof();
}

void loadDB(DB& db, const std::string& src) {
	try {
		logEntry("Loading Database...", EntryType::Access);
		std::ifstream f(src);
		json		  j;
		if (is_empty(f)) {
			std::cout << "Database is not present, someone forgot to create it!"
					  << std::endl;
			exit(1);
		}
		f >> j;
		db = j;
	} catch (const std::exception& ex) {
		std::cout << "Failed loading database from: " << src << std::endl;
		std::cout << "Error: " << ex.what() << std::endl;
	}
}
