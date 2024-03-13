#pragma once

#include<set>
#include<deque>
#include<string>
#include"Competitor.h"
#include"MedalType.h"

using namespace std;

class Medal {
	friend class Competitor;
	set<Competitor*> competitors;
	set<string> disciplines;
	MedalType medalType;
public:
	Medal(MedalType med) : medalType(med) { }
	void addCompetitor(Competitor* com) {
		competitors.insert(com);
	}

	void addDiscipline(string discipline) {
		disciplines.insert(discipline);
	}

	set<Competitor*> getCompetitors() {
		return competitors;
	}


	MedalType getMedalType() {
		return medalType;
	}

	set<string> getDisciplnes() {
		return disciplines;
	}
};


