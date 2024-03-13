#include "Event.h"

Event::Event(string name, string cName){
	fullName = name; city = cName;
	regex rx("(\\d+) ([a-zA-z]+)");
	smatch result;
	if (regex_match(name, result, rx)) {
		year = stoi(result.str(1));
		season = result.str(2);
	}
}
