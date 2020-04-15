#include "log.h"

auto t2str(EntryType type) -> std::string {
	if (type == EntryType::Access)
		return "Type: Access";
	if (type == EntryType::Creation)
		return "Type: Creation";
	if (type == EntryType::Modification)
		return "Type: Modification";
	if (type == EntryType::None)
		return "Type: None";
	return "Type: None";
}

void logEntry(const std::string& msg, EntryType type) {
	Entry ev;
	ev.type		 = type;
	ev.mesg		 = msg;
	ev.timerTime = timer_get();

	time_t	 t		   = time(0);
	struct tm* currentTime = localtime(&t);

	ev.creationDate.day	= currentTime->tm_mday;
	ev.creationDate.month  = currentTime->tm_mon;
	ev.creationDate.year   = currentTime->tm_year + 1900;
	ev.creationDate.hour   = currentTime->tm_hour;
	ev.creationDate.minute = currentTime->tm_min;
	ev.creationDate.second = currentTime->tm_sec;

	if (!s_log.entries)
		s_log.entries = new std::list<Entry>();
	s_log.entries->push_front(ev);
}

void writeLog(const std::string& loc, bool append) {
	std::fstream f;
	if (append)
		f.open(LOC_LOG, std::fstream::out | std::fstream::app);
	else
		f.open(LOC_LOG);

	for (auto entry: *s_log.entries) {
		f << "[ " << entry.creationDate.day << "/" << entry.creationDate.month
		  << "/" << entry.creationDate.year << " ] [ "
		  << entry.creationDate.hour << ":" << entry.creationDate.minute << ":"
		  << entry.creationDate.second << " ] [ "
		  << std::to_string(entry.timerTime) << " ] " << t2str(entry.type)
		  << " - " << entry.mesg << "\n";
	}
	f.close();
}

void printLog(const std::string& loc, int entries) {
	std::fstream f(LOC_LOG);
	std::string  line = "";
	if (entries)
		while (std::getline(f, line) && entries--) {
			std::cout << line << std::endl;
		}
	else
		while (std::getline(f, line)) { std::cout << line << std::endl; }
	f.close();
}
