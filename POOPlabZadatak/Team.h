#pragma once
#include<set>
#include"Competitor.h"
#include"Athlete.h"
#include"MedalType.h"
#include<iostream>
using namespace std;
class Team :public Competitor
{
private:
	set <int> ids;
public:
	Team(MedalType m, string cn, string g, string s) :Competitor(m, cn, g, s) {  };
	void addTeamMember(int id) {
		ids.insert(id);
	}

	string type() {
		return "Team";
	}

	set <int> getIds() {
		return ids;
	}

	int getNumOfTeamsters() {
		return ids.size();
	}


	friend ostream& operator<<(ostream& os, Team& team) {
		os << team.getGame() << " ";
		for (auto elem : team.getIds()) {
			os << elem << " ";
		}
		os << endl;
		return os;
	}
};

