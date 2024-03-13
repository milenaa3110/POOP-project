#pragma once
#include<set>
#include <string>
#include<vector>
#include"MedalType.h"

using namespace std;

class Competitor
{
	MedalType medal;
	string countryName;
	string game;
	string sport;
protected:
	set<int> ids;
public:
	Competitor(MedalType m, string cn, string g, string s) : medal(m), countryName(cn), game(g), sport(s) {};
	virtual string type() = 0;

	MedalType getMedal() {
		return medal;
	}

	string getCountryName() {
		return countryName;
	}

	string getGame() {
		return game;
	}

	string getSport() {
		return sport;
	}

	virtual set<int> getIds() = 0;

	bool operator==(Competitor& com) {
		return getIds() == com.getIds() && countryName == com.getCountryName() && game == com.getGame();
	}
};

