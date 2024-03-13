#pragma once
#include<exception>
using namespace std;
class exceptionFile : public exception {
	virtual const char* what() const throw() {
		return "Problem with file\n";
	}
};

class exceptionFormat : public exception {
	virtual const char* what() const throw() {
		return "Format is not valid\n";
	}
};

class wrongEventNameFormat : public exception {
	virtual const char* what() const throw() {
		return "Event with this name doesn't exists\n";
	}
};

class wrongSportFormat : public exception {
	virtual const char* what() const throw() {
		return "There isn't sport with this name\n";
	}
};

class wrongCountryFormat : public exception {
	virtual const char* what() const throw() {
		return "There isn't country with this name\n";
	}
};

class wrongMedalFormat : public exception {
	virtual const char* what() const throw() {
		return "There isn't medal type with this name\n";
	}
};

class wrongEventYearFormat : public exception {
	virtual const char* what() const throw() {
		return "Event with this year doesn't exists\n";
	}
};

class wrongTypeGameFormat : public exception {
	virtual const char* what() const throw() {
		return "Game with this type doesn't exists\n";
	}
};