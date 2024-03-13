#include<iostream>
#include"Events.h"
#include"MedalType.h"



int main() {
	const char* MAIN_MENU = "\nOptions:\n" \
		"0 - Exit\n" \
		"1 - Load data\n" \
		"2 - Print number of competitors\n" \
		"3 - Print number of disciplines\n" \
		"4 - Print average height of competitors\n"\
		"5 - Print average weight of competitors\n"\
		"6 - Determining the number of different sports in which a given country has won at least one medal\n"\
		"7 - Determining 3 most successful countries at the given enent\n"\
		"8 - Determining all the countries which were at least once the most successful\n"\
		"9 - Determining the ten youngest participants in the Olympic Games who won a medal on their first participation\n"\
		"10 - Getting all pairs of countries - athletes, for all athletes who have won at least one medal in both individual and group competition\n"\
		"11 - Determining all athletes who participated in a given pair of Olympic Games\n"\
		"12 - Getting all the teams that the given country had at the given games\n"\
		"13 - Determining all cities where the Olympic Games have been held at least once\n";

	const char* MENU_1_0 = "group (0) or individual(1) mode (default 0) \n";
	const char* MENU_1_0_a = "Enter year:\n";
	const char* MENU_1_1 = "Enter event name \n";
	const char* MENU_1_2_a = "Filter by sport (0 or 1)\n";
	const char* MENU_1_2_b = "Enter sport\n";
	const char* MENU_1_2_c = "Filter by country (0 or 1)\n";
	const char* MENU_1_2_d = "Enter country\n";
	const char* MENU_1_2_e = "Filter by year(0 or 1)\n";
	const char* MENU_1_2_f = "Enter year\n";
	const char* MENU_1_2_g = "Fiter by type of event (0 or 1)\n";
	const char* MENU_1_2_h = "Enter type\n";
	const char* MENU_1_2_i = "Filter by medal (0 or 1)\n";
	const char* MENU_1_2_j = "Enter medal\n";
	const char* MENU_1_3 = "Enter pair of event names\n";


	printf("DZ1POOP\n");


	int choice = -1;
	int mode, year, filter;
	string sport, country, type, medal, eventName, eventName1, temp;
	Events* events = nullptr;
	bool ret;
	while (choice != 0) {
		cout << MAIN_MENU;
		cin >> choice;
		switch (choice) {

		case 0:
			exit(0);
			break;
		case 1:
			cout << MENU_1_0;
			getline(cin, temp);
			getline(cin, temp);
			if (temp != "0" && temp != "1") mode = 0;
			else mode = stoi(temp);
			if (mode == 1) {
				cout << MENU_1_0_a;
				cin >> year;
				events = new Events(mode, year);
			}
			else {
				events = new Events(mode);
			}
			try {
				events->parse();
			}
			catch (exception& e) {
				cout << e.what() << '\n';
			}
			break;
		case 2:
			try {
				cout << MENU_1_2_a;
				getline(cin, temp);
				getline(cin, temp);
				if (temp != "0" && temp != "1") filter = 0;
				else filter = stoi(temp);
				if (filter) {
					cout << MENU_1_2_b;
					getline(cin, sport);
					if (events) events->filterSport(sport);
				}
				cout << MENU_1_2_c;
				getline(cin, temp);
				if (temp != "0" && temp != "1") filter = 0;
				else filter = stoi(temp);
				if (filter) {
					cout << MENU_1_2_d;
					getline(cin, country);
					if (events) events->filterCountry(country);
				}
				cout << MENU_1_2_e;
				getline(cin, temp);
				if (temp != "0" && temp != "1") filter = 0;
				else filter = stoi(temp);
				if (filter) {
					cout << MENU_1_2_f;
					getline(cin, temp);
					year = stoi(temp);
					if (events) events->filterYear(year);
				}
				cout << MENU_1_2_g;
				getline(cin, temp);
				if (temp != "0" && temp != "1") filter = 0;
				else filter = stoi(temp);
				if (filter) {
					cout << MENU_1_2_h;
					getline(cin, type);
					if (events) events->filterTypeEvent(type);
				}
				cout << MENU_1_2_i;
				getline(cin, temp);
				if (temp != "0" && temp != "1") filter = 0;
				else filter = stoi(temp);
				if (filter) {
					cout << MENU_1_2_j;
					getline(cin, medal);
					if (events) events->filterMedal(medal);
				}
			}
			catch (exception& e) {
				cout << e.what() << '\n';
			}
			if (events) cout << events->numOfCompetitors();
			break;
		case 3:
			try {
				cout << MENU_1_2_a;
				getline(cin, temp);
				getline(cin, temp);
				if (temp != "0" && temp != "1") filter = 0;
				else filter = stoi(temp);
				if (filter) {
					cout << MENU_1_2_b;
					getline(cin, sport);
					if (events) events->filterSport(sport);
				}
				cout << MENU_1_2_c;
				getline(cin, temp);
				if (temp != "0" && temp != "1") filter = 0;
				else filter = stoi(temp);
				if (filter) {
					cout << MENU_1_2_d;
					getline(cin, country);
					if (events) events->filterCountry(country);
				}
				cout << MENU_1_2_e;
				getline(cin, temp);
				if (temp != "0" && temp != "1") filter = 0;
				else filter = stoi(temp);
				if (filter) {
					cout << MENU_1_2_f;
					getline(cin, temp);
					year = stoi(temp);
					if (events) events->filterYear(year);
				}
				cout << MENU_1_2_g;
				getline(cin, temp);
				if (temp != "0" && temp != "1") filter = 0;
				else filter = stoi(temp);
				if (filter) {
					cout << MENU_1_2_h;
					getline(cin, type);
					if (events) events->filterTypeEvent(type);
				}
				cout << MENU_1_2_i;
				getline(cin, temp);
				if (temp != "0" && temp != "1") filter = 0;
				else filter = stoi(temp);
				if (filter) {
					cout << MENU_1_2_j;
					getline(cin, medal);
					if (events) events->filterMedal(medal);
				}
			}
			catch (exception& e) {
				cout << e.what() << '\n';
			}
			if (events) cout << events->numOfdisciplines();
			break;
		case 4:
			try {
				cout << MENU_1_2_a;
				getline(cin, temp);
				getline(cin, temp);
				if (temp != "0" && temp != "1") filter = 0;
				else filter = stoi(temp);
				if (filter) {
					cout << MENU_1_2_b;
					getline(cin, sport);
					if (events) events->filterSport(sport);
				}
				cout << MENU_1_2_c;
				getline(cin, temp);
				if (temp != "0" && temp != "1") filter = 0;
				else filter = stoi(temp);
				if (filter) {
					cout << MENU_1_2_d;
					getline(cin, country);
					if (events) events->filterCountry(country);
				}
				cout << MENU_1_2_e;
				getline(cin, temp);
				if (temp != "0" && temp != "1") filter = 0;
				else filter = stoi(temp);
				if (filter) {
					cout << MENU_1_2_f;
					getline(cin, temp);
					year = stoi(temp);
					if (events) events->filterYear(year);
				}
				cout << MENU_1_2_g;
				getline(cin, temp);
				if (temp != "0" && temp != "1") filter = 0;
				else filter = stoi(temp);
				if (filter) {
					cout << MENU_1_2_h;
					getline(cin, type);
					if (events) events->filterTypeEvent(type);
				}
				cout << MENU_1_2_i;
				getline(cin, temp);
				if (temp != "0" && temp != "1") filter = 0;
				else filter = stoi(temp);
				if (filter) {
					cout << MENU_1_2_j;
					getline(cin, medal);
					if (events) events->filterMedal(medal);
				}
			}
			catch (exception& e) {
				cout << e.what() << '\n';
			}
			if (events) cout << events->averageHeight();
			break;
		case 5:
			try {
				cout << MENU_1_2_a;
				getline(cin, temp);
				getline(cin, temp);
				if (temp != "0" && temp != "1") filter = 0;
				else filter = stoi(temp);
				if (filter) {
					cout << MENU_1_2_b;
					getline(cin, sport);
					if (events) events->filterSport(sport);
				}
				cout << MENU_1_2_c;
				getline(cin, temp);
				if (temp != "0" && temp != "1") filter = 0;
				else filter = stoi(temp);
				if (filter) {
					cout << MENU_1_2_d;
					getline(cin, country);
					if (events) events->filterCountry(country);
				}
				cout << MENU_1_2_e;
				getline(cin, temp);
				if (temp != "0" && temp != "1") filter = 0;
				else filter = stoi(temp);
				if (filter) {
					cout << MENU_1_2_f;
					getline(cin, temp);
					year = stoi(temp);
					if (events) events->filterYear(year);
				}
				cout << MENU_1_2_g;
				getline(cin, temp);
				if (temp != "0" && temp != "1") filter = 0;
				else filter = stoi(temp);
				if (filter) {
					cout << MENU_1_2_h;
					getline(cin, type);
					if (events) events->filterTypeEvent(type);
				}
				cout << MENU_1_2_i;
				getline(cin, temp);
				if (temp != "0" && temp != "1") filter = 0;
				else filter = stoi(temp);
				if (filter) {
					cout << MENU_1_2_j;
					getline(cin, medal);
					if (events) events->filterMedal(medal);
				}
			}
			catch (exception& e) {
				cout << e.what() << '\n';
			}
			if (events) cout << events->averageWeight();
			break;
		case 6:
			cout << MENU_1_2_d;
			getline(cin, country);
			getline(cin, country);
			try {
				if (events) cout << events->findSports(country) << endl;
			}
			catch (exception& e) {
				cout << e.what() << '\n';
			}
			break;
		case 7:
			cout << MENU_1_1;
			getline(cin, eventName);
			getline(cin, eventName);
			try {
				if (events) events->findThreeBest(eventName);
			}
			catch (exception& e) {
				cout << e.what() << '\n';
			}
			break;
		case 8:
			if (events) events->bestOnce();
			break;
		case 9:
			if (events) events->findTenYoungest();
			break;
		case 10:
			if (events) events->findBothTeamandIndividualMedal();
			break;
		case 11:
			cout << MENU_1_3;
			getline(cin, eventName);
			getline(cin, eventName);
			getline(cin, eventName1);
			try {
				if (events) events->allPairSpotsmen(eventName, eventName1);
			}
			catch (exception& e) {
				cout << e.what() << '\n';
			}
			break;
		case 12:
			cout << MENU_1_1;
			getline(cin, eventName);
			getline(cin, eventName);
			cout << MENU_1_2_d;
			getline(cin, country);
			try {
				if (events) events->findAllTeams(country, eventName);
			}
			catch (exception& e) {
				cout << e.what() << '\n';
			}
			break;
		case 13:
			if (events) cout << events->eventCities() << endl;
			break;
		}
	}
	return 0;
}