#pragma once
#include <string>
#include <set>
using namespace std;

class Country
{
	set<string> countries;
public:
	void addCountry(string country) {
		countries.insert(country);
	}

	set<string> getCountry() {
		return countries;
	}
};

