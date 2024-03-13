#include "Events.h"


MedalType Events::getMedal(string m) {
	if (m == "Gold") return MedalType::Gold;
	if (m == "Silver") return MedalType::Silver;
	if (m == "Bronze") return MedalType::Bronze;
	if (m == "") return MedalType::None;
	throw wrongMedalFormat();
}

void Events::competitorFilterNeutral()
{
	for (auto event : events) {
		for (auto game : event.second->getGames()) {
			set<Competitor*> gameCompetitors = game->getCompetitors();
			competitorFilter.insert(gameCompetitors.begin(), gameCompetitors.end());
		}
	}
}


void Events::parse()
{
	set<int> distinctIds;
	string textLine;
	Event* currEvent = nullptr; Game* currGames = nullptr; Competitor* currCompetitor = nullptr; Sport* currSport = nullptr;
	ifstream file1("C:\\Users\\Milena\\Downloads\\13S112POOP\\events\.txt");
	if (!file1.is_open()) {
		throw exceptionFile();
	}
	regex rx2("([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^\\n]*)");
	while (getline(file1, textLine)) {
		smatch result;
		if (regex_match(textLine, result, rx2)) {
			string eventName = result.str(1);
			regex rx("(\\d+) ([a-zA-z]+)");
			smatch result1;
			int year = 0;
			if (regex_match(eventName, result1, rx)) {
				year = stoi(result1.str(1));
				string season = result1.str(2);
			}
			if (mod == 0 || (mod == 1 && filter == year)) {
				string city = result.str(2);
				string sport = result.str(3);
				string discipline = result.str(4);
				string type = result.str(5);
				string country = result.str(6);
				string competitorsNames = result.str(7);
				string medal = result.str(8);
				MedalType med = getMedal(medal);
				
				allCountries->addCountry(country); allSports->addSport(sport);
				if (type == "Team") {
					regex rx3(".'(\\d+)'.");
					regex_token_iterator<std::string::const_iterator> rend;
					Team* team = new Team(med, country, discipline, sport);
					for (auto i = sregex_token_iterator(competitorsNames.begin(), competitorsNames.end(), rx3, 1); i != rend; i++) {
						int num = stoi(i->str());
						distinctIds.insert(num);
						team->addTeamMember(num);
					}
					currCompetitor = team;
				}
				else {
					Athlete* athlete = new Athlete(stoi(competitorsNames), med, country, discipline, sport);
					distinctIds.insert(stoi(competitorsNames));
					currCompetitor = athlete;
				}
				

				if (currEvent == nullptr || currEvent->getFullName() != eventName) {
					currEvent = new Event(eventName, city); events.insert({ eventName, currEvent });
				}
				if (currEvent->getGames().size() == 0 || currGames->getDiscipline() != discipline) {
					currGames = new Game(discipline, sport); currEvent->addNewgames(currGames);
				}
				currGames->addNewCompetitor(currCompetitor);
			}

		}
		else throw exceptionFormat();
	}
	
	ifstream file2("C:\\Users\\Milena\\Downloads\\13S112POOP\\athletes\.txt");
	if (!file2.is_open()) {
		throw exceptionFile();
	}
	regex rx1("([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^\\n]*)");
	int last = (int)(*(--distinctIds.end()));
	while (getline(file2, textLine)) {
		smatch result;
		vector <string> data;
		if (regex_match(textLine, result, rx1)) {
			int id = stoi(result.str(1));
			if (id > last) break;
			if (distinctIds.find(id) != distinctIds.end()) {
				vector<string> data;
				data.resize(5);
				data[0] = result.str(2);
				data[1] = result.str(3);
				data[2] = result.str(4) == "NA" ? "0" : result.str(4);
				data[3] = result.str(5) == "NA" ? "0.0" : result.str(5);
				data[4] = result.str(6) == "NA" ? "0.0" : result.str(6);
				athleteData.insert({ id, new AthleteInfo(data) });
			}
		}
		else throw exceptionFormat();

	}
	competitorFilterNeutral();
}

void Events::filterCountry(string countryName)
{
	set<Competitor*> competitorFilter1;
	set<string> allCountriesSet = allCountries->getCountry();
	if (allCountriesSet.find(countryName) == allCountriesSet.end()) throw wrongCountryFormat();
	vector<Competitor*> competitorCountries = findCompetitorsByCountry(countryName);
	for (auto com : competitorCountries) {
		if (competitorFilter.find(com) != competitorFilter.end()) competitorFilter1.insert(com);
	}
	competitorFilter = competitorFilter1;
}

void Events::filterYear(int year)
{
	set<Competitor*> competitorFilter1;
	deque<Event*> eventsByYear = findEventByYear(year);
	if (eventsByYear.size() == 0) throw wrongEventYearFormat();
	for (auto event : eventsByYear) {
		for (auto game : event->getGames()) {
			set<Competitor*> gameCompetitors = game->getCompetitors();
			for (auto com : gameCompetitors) {
				if (competitorFilter.find(com) != competitorFilter.end()) competitorFilter1.insert(com);
			}
		}
	}
	competitorFilter = competitorFilter1;
}

void Events::filterTypeEvent(string type)
{
	set<Competitor*> competitorFilter1;
	if (type != "Team" && type != "Individual") throw wrongTypeGameFormat();
	for (auto event : events) {
		for (auto game : event.second->getGames()) {
			if (game->getType() == type) {
				set<Competitor*> gameCompetitors = game->getCompetitors();
				for (auto com : game->getCompetitors()) {
					if (competitorFilter.find(com) != competitorFilter.end()) competitorFilter1.insert(com);
				}
			}
		}
	}
	competitorFilter = competitorFilter1;
}

void Events::filterMedal(string m)
{
	MedalType medalType = getMedal(m);
	vector<Competitor*> competitorsMedal = findCompetitorsByMedal(medalType);
	set<Competitor*> competitorFilter1;
	for (auto com : competitorsMedal) {
		if (competitorFilter.find(com) != competitorFilter.end()) competitorFilter1.insert(com);
	}
	competitorFilter = competitorFilter1;
}


bool cmp(pair<string, vector<int>>& a, pair<string, vector<int>>& b) {
	return (a.second[0] < b.second[0] || (a.second[0] == b.second[0] && a.second[1] < b.second[1]) || (a.second[0] == b.second[0] && a.second[1] == b.second[1] && a.second[2] < b.second[2]));
}

string Events::findThreeBest(string eventName)
{
	if (events.find(eventName) == events.end()) throw wrongEventNameFormat();
	Event* event = events[eventName];
	vector<pair<string, vector<int>>> pairs = findTheBest(event);
	int n = pairs.size() - 1;
	for (int i = 0; i < 3; i++) {
		cout << pairs[n--].first << endl;
	}
	return pairs[pairs.size() - 1].first;

}

vector<pair<string, vector<int>>> Events::findTheBest(Event* event) {
	map <string, vector<int>> countrySuccess;
	for (auto game : event->getGames()) {
		if (game->getFirstPlace() != nullptr) {
			if (countrySuccess.find(game->getFirstPlace()->getCountryName()) == countrySuccess.end()) {
				vector<int> data; data.resize(3); data[0] = 1; data[1] = 0; data[2] = 0;
				countrySuccess.insert({ game->getFirstPlace()->getCountryName(), data });
			}
			else {
				countrySuccess[game->getFirstPlace()->getCountryName()][0]++;
			}
		}
		if (game->getSecondPlace() != nullptr) {
			if (countrySuccess.find(game->getSecondPlace()->getCountryName()) == countrySuccess.end()) {
				vector<int> data; data.resize(3); data[0] = 0; data[1] = 1; data[2] = 0;
				countrySuccess.insert({ game->getFirstPlace()->getCountryName(), data });
			}
			else {
				countrySuccess[game->getSecondPlace()->getCountryName()][1]++;
			}
		}
		if (game->getThirdPlace() != nullptr) {
			if (countrySuccess.find(game->getThirdPlace()->getCountryName()) == countrySuccess.end()) {
				vector<int> data; data.resize(3); data[0] = 0; data[1] = 0; data[2] = 1;
				countrySuccess.insert({ game->getFirstPlace()->getCountryName(), data });
			}
			else {
				countrySuccess[game->getThirdPlace()->getCountryName()][2]++;
			}
		}
	}
	vector<pair<string, vector<int>>> pairs;
	pairs.resize(countrySuccess.size());
	copy(countrySuccess.begin(), countrySuccess.end(), pairs.begin());
	sort(pairs.begin(), pairs.end(), cmp);
	return pairs;
}

void Events::bestOnce()
{
	set<string> countriesBest;
	for (auto event : events) {
		vector<pair<string, vector<int>>> pairs = findTheBest(event.second);
		countriesBest.insert(pairs[pairs.size() - 1].first);
	}
	for (auto i : countriesBest) {
		cout << i << endl;
	}
}

void Events::filterSport(string sportName){
	set<Competitor*> competitorFilter1;
	set<string> allSportsSet = allSports->getSports();
	if (allSportsSet.find(sportName) == allSportsSet.end()) throw wrongSportFormat();
	vector<Competitor*> competitorSports = findCompetitorsBySport(sportName);
	for (auto com : competitorSports) {
		if (competitorFilter.find(com) != competitorFilter.end()) competitorFilter1.insert(com);
	}

	competitorFilter = competitorFilter1;
}

int Events::eventCities() {
	set<string> cities;
	for (auto event : events) {
		cities.insert(event.second->getCity());
	}
	for (auto city : cities) {
		cout << city << endl;
	}
	return cities.size();
}

int Events::findSports(string countryName) {
	set<string> allCountriesSet = allCountries->getCountry();
	if (allCountriesSet.find(countryName) == allCountriesSet.end()) throw wrongCountryFormat();
	set<string> sportNames;
	vector<Competitor*> competitorsCountry = findCompetitorsByCountry(countryName);
	for (auto com : competitorsCountry) {
		if (com->getMedal() != MedalType::None) sportNames.insert(com->getSport());
	}
	return sportNames.size();
}

void Events::findTenYoungest() {
	map<int, AthleteInfo*> athleteData1 = athleteData;
	map<int, int> competitorYears;
	set<int> deletedIds;
	vector<pair<string, Event*>> eventsVector;
	eventsVector.resize(events.size());
	copy(events.begin(), events.end(), eventsVector.begin());
	sort(eventsVector.begin(), eventsVector.end(), [](pair<string, Event*> a, pair<string, Event*> b) {return a.second->getYear() < b.second->getYear(); });
	for (auto event : eventsVector) {
		for (auto game : event.second->getGames()) {
			if (game->getFirstPlace() != nullptr) {
				for (auto id : game->getFirstPlace()->getIds()) {
					if (athleteData1.find(id) != athleteData1.end() && athleteData1[id]->getYear() != 0) competitorYears.insert({ id, athleteData1[id]->getYear() });
				}
			}
			if (game->getSecondPlace() != nullptr) {
				for (auto id : game->getSecondPlace()->getIds()) {
					if (athleteData1.find(id) != athleteData1.end() && athleteData1[id]->getYear() != 0) competitorYears.insert({ id, athleteData1[id]->getYear() });
				}
			}
			if (game->getThirdPlace() != nullptr) {
				for (auto id : game->getThirdPlace()->getIds()) {
					if (athleteData1.find(id) != athleteData1.end() && athleteData1[id]->getYear() != 0) competitorYears.insert({ id, athleteData1[id]->getYear() });
				}
			}
			for (auto com : game->getCompetitors()) {
				for (auto id : com->getIds()) {
					deletedIds.insert(id);
				}
			}
		}
		for (auto id : deletedIds) {
			athleteData1.erase(id);
		}
	}
	vector<pair<int, int>> pairs;
	pairs.resize(competitorYears.size());
	copy(competitorYears.begin(), competitorYears.end(), pairs.begin());
	sort(pairs.begin(), pairs.end(), [](pair<int, int> a, pair<int, int> b) {return a.second < b.second; });
	for (int i = 0; i < 10; i++) {
		cout << pairs[i].first << " " << pairs[i].second << endl;
	}
}

void Events::allPairSpotsmen(string eventName1, string eventName2)
{
	set<int> sports1, sports2;
	if (events.find(eventName1) == events.end()) throw wrongEventNameFormat();
	if (events.find(eventName2) == events.end()) throw wrongEventNameFormat();

	Event* event1 = events[eventName1];
	Event* event2 = events[eventName2];
	

	for (auto game : event1->getGames()) {
		for (auto id : game->getIds()) {
			sports1.insert(id);
		}
	}
	for (auto game : event2->getGames()) {
		for (auto id : game->getIds()) {
			sports2.insert(id);
		}
	}
	vector<int> v_intersection;
	set_intersection(sports1.begin(), sports1.end(), sports2.begin(), sports2.end(), back_inserter(v_intersection));
	for (auto elem : v_intersection) {
		cout << elem << endl;
	}
}

vector<pair<string, int>> Events::findBothTeamandIndividualMedal() {
	set<pair<string, int>>  pairsTeam;
	set<pair<string, int>> pairsIndividual;
	filterTypeEvent("Individual");
	for (auto com : competitorFilter) {
		if (com->getMedal() != MedalType::None)	{
			for (auto id : com->getIds()) {
				pairsIndividual.insert({ com->getCountryName(), id });
			}
		}
	}
	competitorFilterNeutral();
	filterTypeEvent("Team");
	for (auto com : competitorFilter) {
		if (com->getMedal() != MedalType::None) {
			for (auto id : com->getIds()) {
				pairsTeam.insert({ com->getCountryName(), id });
			}
		}
	}
	competitorFilterNeutral();
	vector<pair<string, int>> v_intersection;
	set_intersection(pairsTeam.begin(), pairsTeam.end(), pairsIndividual.begin(), pairsIndividual.end(), back_inserter(v_intersection));
	for (auto elem : v_intersection) {
		cout << elem.first << " " << elem.second << endl;
	}
	return v_intersection;
}

void Events::findAllTeams(string countryName, string eventName)
{
	deque<Team*> teams;
	if (events.find(eventName) == events.end()) throw wrongEventNameFormat();
	set<string> countriesAllSet = allCountries->getCountry();
	if (countriesAllSet.find(countryName) == countriesAllSet.end()) throw wrongCountryFormat();
	Event* event = events[eventName];
	set<Competitor*> comEvent;
	for (auto game : event->getGames()) {
		set<Competitor*>setGame = game->getCompetitors();
		comEvent.insert(setGame.begin(), setGame.end());
	}
	vector <Competitor*> competitorsCountry = findCompetitorsByCountry(countryName);
	set <Competitor*> comCountry;
	for (auto com : competitorsCountry) {
		comCountry.insert(com);
	}
	vector<Competitor*> v_intersection;

	set_intersection(comEvent.begin(), comEvent.end(), comCountry.begin(), comCountry.end(), back_inserter(v_intersection));
	for (auto elem : v_intersection) {
		if (elem->type() == "Team") teams.push_back((Team*)elem);
	}
	sort(teams.begin(), teams.end(), [](Team* a, Team* b) {return a->getNumOfTeamsters() > b->getNumOfTeamsters() || a->getNumOfTeamsters() == b->getNumOfTeamsters() && a->getGame() < b->getGame(); });
	for (auto elem : teams) {
		cout << *elem;
	}
}



deque<Event*> Events::findEventByYear(int year)
{
	deque<Event*> returnedEvents;
	vector<pair<string, Event*>> eventsVector;
	copy(events.begin(), events.end(), back_inserter(eventsVector));
	auto found = eventsVector.begin();
	while (found != eventsVector.end()) {
		found = find_if(found, eventsVector.end(), [year](pair<string, Event*> & a) {return a.second->getYear()==year; });
		if (found != eventsVector.end()) {
			returnedEvents.push_back((*found).second);
			found++;
		}
	}
	return returnedEvents;
}

vector<Competitor*> Events::findCompetitorsByCountry(string countryName)
{
	vector<Competitor*> competitorsCountry;
	for (auto event : events) {
		for (auto game : event.second->getGames()) {
			set<Competitor*> gameCompetitors = game->getCompetitors();
			auto found = gameCompetitors.begin();
			while (found != gameCompetitors.end()) {
				found = find_if(found, gameCompetitors.end(), [countryName](Competitor* a) {return a->getCountryName() == countryName; });
				if (found != gameCompetitors.end()) {
					competitorsCountry.push_back(*found);
					found++;
				}
			}
		}
	}
	return competitorsCountry;
}

vector<Competitor*> Events::findCompetitorsBySport(string sportName)
{
	vector<Competitor*> competitorSport;
	for (auto event : events) {
		deque<Game*> games = event.second->getGames();
		auto found = games.begin();
		while (found != games.end()) {
			found = find_if(found, games.end(), [sportName](Game* a) {return a->getSport() == sportName; });
			if (found != games.end()) {
				for (auto com : (*found)->getCompetitors()) {
					competitorSport.push_back(com);
				}
				found++;
			}
		}
	}
	return competitorSport;
}

vector <Competitor*> Events::findCompetitorsByMedal(MedalType med)
{
	vector<Competitor*> competitorsMedal;
	for (auto event : events) {
		for (auto game : event.second->getGames()) {
			set<Competitor*> gameCompetitors = game->getCompetitors();
			auto found = gameCompetitors.begin();
			while (found != gameCompetitors.end()) {
				found = find_if(found, gameCompetitors.end(), [med](Competitor* a) {return a->getMedal() == med; });
				if (found != gameCompetitors.end()) {
					competitorsMedal.push_back(*found);
					found++;
				}
			}
		}
	}
	return competitorsMedal;
}

int Events::numOfdisciplines()
{
	set <string> disciplinesFilter;
	for (auto com : competitorFilter) {
		disciplinesFilter.insert(com->getGame());
	}
	int num = disciplinesFilter.size();
	competitorFilterNeutral();
	return num;
}

int Events::numOfCompetitors() {
	map <int, AthleteInfo*> athleteDataFilter;
	for (auto com : competitorFilter) {
		for (auto id : com->getIds()) {
			athleteDataFilter[id] = athleteData[id];
		}
	}
	int num = athleteDataFilter.size();
	competitorFilterNeutral();
	return num;
}

float Events::averageHeight(){
	map <int, AthleteInfo*> athleteDataFilter;
	double sum = 0.0; int num = 0;
	for (auto com : competitorFilter) {
		for (auto id : com->getIds()) {
			athleteDataFilter[id] = athleteData[id];
		}
	}
	for (auto elem : athleteDataFilter) {
		if (elem.second->getHeight() != 0.0) {
			sum += elem.second->getHeight();
			 num++;
		}
	}
	sum = sum / num;
	competitorFilterNeutral();
	return sum;
}

float Events::averageWeight(){
	map <int, AthleteInfo*> athleteDataFilter;
	double sum = 0.0; int num = 0;
	for (auto com : competitorFilter) {
		for (auto id : com->getIds()) {
			athleteDataFilter[id] = athleteData[id];
		}
	}

	for (auto elem : athleteDataFilter) {
		if (elem.second->getWeight() != 0.0) {
			sum += elem.second->getWeight();
			num++;
		}
	}
	
	sum = sum / num;
	competitorFilterNeutral();
	return sum;
}
