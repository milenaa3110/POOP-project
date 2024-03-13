#pragma once
#include<algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include"Exceptions.h"
#include<vector>
#include<deque>
#include<set>
#include<map>
#include"Game.h"
#include"Competitor.h"
#include"Athlete.h"
#include"Event.h"
#include "Sport.h"
#include"MedalType.h"
#include"Team.h"
#include"Country.h"
#include"AthleteInfo.h"
using namespace std;


class Events
{
private:
	int mod;
	int filter;
	
	
	set<Competitor*> competitorFilter;
	Sport* allSports;
	Country* allCountries;
	map <int, AthleteInfo*> athleteData;
	map<string, Event*> events;
	vector<pair<string, vector<int>>> findTheBest(Event* event);
	deque<Event*> findEventByYear(int year);
	vector<Competitor*> findCompetitorsByCountry(string countryName);
	vector<Competitor*> findCompetitorsBySport(string sportName);
	vector<Competitor*> findCompetitorsByMedal(MedalType med);
	MedalType getMedal(string m);
	void competitorFilterNeutral();
public:
	Events(int m, int f = 0) : mod(m), filter(f) { allCountries = new Country; allSports = new Sport; }
	void parse();

	int numOfdisciplines(); 
	int numOfCompetitors();

	float averageHeight();

	float averageWeight();

	void filterSport(string sportName);
	void filterCountry(string countryName);
	void filterYear(int year);
	void filterTypeEvent(string type);
	void filterMedal(string m);

	int eventCities();
	int findSports(string countryName);
	string findThreeBest(string eventName);
	void bestOnce();
	void findTenYoungest();
	void allPairSpotsmen(string eventName1, string eventName2);
	vector<pair<string, int>> findBothTeamandIndividualMedal();
	void findAllTeams(string countryName, string eventName);
};

