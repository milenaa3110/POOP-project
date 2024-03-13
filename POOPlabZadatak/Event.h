#pragma once
#include<regex>
#include <deque>
#include"Game.h"
using namespace std;

class Event
{
private:

	int year;
	string season;
	string city;
	string fullName;
	deque <Game*> games;
public:
	friend class Events;
	Event(string name, string cName);

	int getYear() {
		return year;
	}

	string getSeason() {
		return season;
	}
	

	string getFullName() {
		return fullName;
	}

	string getCity() {
		return city;
	}

	void addNewgames(Game* game) {
		games.push_back(game);
		
		
	}
	deque<Game*> getGames() {
		return games;
	}


	bool operator==(Event& ev1) {
		return getFullName() == ev1.getFullName();
	}
};

