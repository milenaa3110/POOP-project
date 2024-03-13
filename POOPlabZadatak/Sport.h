#pragma once
#include<string>
#include<set>

using namespace std;

class Sport
{
	set<string> sports;
public:
	void addSport(string sport) {
		sports.insert(sport);
	}

	set<string> getSports() {
		return sports;
	}

};

