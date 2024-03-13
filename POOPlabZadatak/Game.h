#pragma once
#include <string>
#include <set>
#include<deque>
#include"Competitor.h"
#include"MedalType.h"
class Game
{
	string gameName;
	string sport;
	string type;
	set<Competitor*> gameCompetitors;
	set<int> ids;
	Competitor* firstPlace;
	Competitor* secondPlace;
	Competitor* thirdPlace;

public:
	Game(string gn, string s) : gameName(gn), sport(s) { firstPlace = nullptr; secondPlace = nullptr; thirdPlace = nullptr; }

	void addNewCompetitor(Competitor* com) {
		gameCompetitors.insert(com);
		for (auto id : com->getIds()) {
			ids.insert(id);
		}
		if (com->getMedal() == MedalType::Gold) firstPlace = com;
		if (com->getMedal() == MedalType::Silver) secondPlace = com;
		if (com->getMedal() == MedalType::Bronze) thirdPlace = com;
		type = com->type();
	}
	string getType() {
		return type;
	}

	string getDiscipline() {
		return gameName;
	}

	string getSport() {
		return sport;
	}

	set<Competitor*> getCompetitors() {
		return gameCompetitors;
	}

	Competitor* getFirstPlace() {
		return firstPlace;
	}

	Competitor* getSecondPlace() {
		return secondPlace;
	}

	Competitor* getThirdPlace() {
		return thirdPlace;
	}

	set<int> getIds() {
		return ids;
	}
};

