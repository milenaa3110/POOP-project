#pragma once
#include "Competitor.h"
#include"MedalType.h"
using namespace std;

class Athlete : public Competitor
{
private:
	

public:
	Athlete(int i, MedalType m, string cn, string go, string s) : Competitor(m, cn, go, s) { ids.insert(i); };
	string type() {
		return "Individual";
	}

	set<int> getIds() {
		return ids;
	}

	bool operator<(Athlete ath1) {
		return *ids.begin() < *ath1.getIds().begin();
	}

};

