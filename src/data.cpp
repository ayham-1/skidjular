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
		{"date", skid.date},
	};
}
void from_json(const json& j, Skid& skid) {
	skid.projects = new Project();
	j.at("projects").get_to(*skid.projects);
	j.at("creationDate").get_to(skid.creationDate);
	j.at("date").get_to(skid.date);
}
void to_json(json& j, const DB& db) {
	std::map<std::string, Project> projects;
	if (db.projects != nullptr) {
		projects = *db.projects;
	};
	j = json{{"projects", projects},
			 {"creationDate", db.creationDate},
			 {"lastAccessTime", db.lastAccessTime},
			 {"lastSkidID", db.lastSkidID}};
}
void from_json(const json& j, DB& db) {
	db.projects = new std::map<std::string, Project>();
	j.at("projects").get_to(*db.projects);
	j.at("creationDate").get_to(db.creationDate);
	j.at("lastAccessTime").get_to(db.lastAccessTime);
	j.at("lastSkidID").get_to(db.lastSkidID);
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

void writeSkid(Skid skid, int skidNum) {
	std::string dest = LOC_SKIDID + std::to_string(skidNum);
	try {
		logEntry("Writing Skid...", EntryType::Modification);
		std::ofstream f(dest);
		json		  j = skid;
		f << j;
	} catch (std::exception& ex) {
		std::cout << "Failed writing skid to: " << dest << std::endl;
		std::cout << "Error: " << ex.what() << std::endl;
	}
}

void loadSkid(Skid& skid, int skidNum) {
	std::string dest = LOC_SKIDID + std::to_string(skidNum);
	try {
		logEntry("Loading Skid...", EntryType::Access);
		std::ifstream f(dest);
		json		  j;
		if (is_empty(f)) {
			std::cout << "Skid is not present" << std::endl;
			exit(1);
		}
		f >> j;
		skid = j;
	} catch (const std::exception& ex) {
		std::cout << "Failed loading skid from: " << dest << std::endl;
		std::cout << "Error: " << ex.what() << std::endl;
	}
}

Date get_today() {
	Date	   res;
	time_t	   t		   = time(0);
	struct tm* currentTime = localtime(&t);

	res.day	  = currentTime->tm_mday;
	res.month = currentTime->tm_mon;
	res.year  = currentTime->tm_year + 1900;

	return res;
}

int get_day_num(Date initial) {
	auto m = (initial.month + 9) % 12;
	auto y = initial.year - m / 10;
	return 365 * y + y / 4 - y / 100 + y / 400 + (m * 306 + 5) / 10 +
		   (initial.day - 1);
}

Date get_day_date(int g) {
	auto y	 = (10000 * g + 14780) / 3652425;
	auto ddd = g - (365 * y + y / 4 - y / 100 + y / 400);
	if (ddd < 0)
		y = y - 1;
	ddd		= g - (365 * y + y / 4 - y / 100 + y / 400);
	auto mi = (100 * ddd + 52) / 3060;
	auto mm = (mi + 2) % 12 + 1;
	y		= y + (mi + 2) / 12;
	auto dd = ddd - (mi * 306 + 5) / 10 + 1;

	Date res;
	res.year  = y;
	res.month = mm;
	res.day	  = dd;
	return res;
}

bool is_empty(std::ifstream& pFile) {
	return pFile.peek() == std::ifstream::traits_type::eof();
}

bool is_path_exist(const std::string& s) {
	struct stat buffer;
	return (stat(s.c_str(), &buffer) == 0);
}

///////////////// COPIED CODE
using namespace std;

// Return if year is leap year or not.
bool isLeap(int y) {
	if (y % 100 != 0 && y % 4 == 0 || y % 400 == 0)
		return true;

	return false;
}

// Given a date, returns number of days elapsed
// from the  beginning of the current year (1st
// jan).
int offsetDays(int d, int m, int y) {
	int offset = d;

	switch (m - 1) {
		case 11: offset += 30;
		case 10: offset += 31;
		case 9: offset += 30;
		case 8: offset += 31;
		case 7: offset += 31;
		case 6: offset += 30;
		case 5: offset += 31;
		case 4: offset += 30;
		case 3: offset += 31;
		case 2: offset += 28;
		case 1: offset += 31;
	}

	if (isLeap(y) && m > 2)
		offset += 1;

	return offset;
}

// Given a year and days elapsed in it, finds
// date by storing results in d and m.
void revoffsetDays(int offset, int y, int* d, int* m) {
	int month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (isLeap(y))
		month[2] = 29;

	int i;
	for (i = 1; i <= 12; i++) {
		if (offset <= month[i])
			break;
		offset = offset - month[i];
	}

	*d = offset;
	*m = i;
}

// Add x days to the given date.
Date addDays_date(Date date, int x) {
	auto d1		 = date.day;
	auto m1		 = date.month;
	auto y1		 = date.year;
	int	 offset1 = offsetDays(d1, m1, y1);
	int	 remDays = isLeap(y1) ? (366 - offset1) : (365 - offset1);

	// y2 is going to store result year and
	// offset2 is going to store offset days
	// in result year.
	int y2, offset2;
	if (x <= remDays) {
		y2		= y1;
		offset2 = offset1 + x;
	}

	else {
		// x may store thousands of days.
		// We find correct year and offset
		// in the year.
		x -= remDays;
		y2		   = y1 + 1;
		int y2days = isLeap(y2) ? 366 : 365;
		while (x >= y2days) {
			x -= y2days;
			y2++;
			y2days = isLeap(y2) ? 366 : 365;
		}
		offset2 = x;
	}

	// Find values of day and month from
	// offset of result year.
	int m2, d2;
	revoffsetDays(offset2, y2, &d2, &m2);

	Date res;
	res.day	  = d2;
	res.month = m2;
	res.year  = y2;
	return res;
}
/////////////////////////////
