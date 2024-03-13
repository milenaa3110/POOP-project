#pragma once
#include <string>
#include <iostream>
#include<vector>

using namespace std;

class AthleteInfo {

	string name;
	int year;
	char gender;
	double height;
	double weight;

public:

	AthleteInfo(vector<string> info) { name = info[0]; gender = info[1][0]; year = stoi(info[2]); height = stod(info[3]); weight = stod(info[4]); }

	string getName() {
		return name;
	}

	int getYear() {
		return year;
	}

	char getGender() {
		return gender;
	}

	double getHeight() {
		return height;
	}

	double getWeight() {
		return weight;
	}

	friend ostream& operator<<(ostream& os, AthleteInfo& athleteInfo) {
		os << athleteInfo.name << " " << athleteInfo.gender << " " << athleteInfo.year << " " << athleteInfo.height << " " << athleteInfo.weight << endl;
		return os;
	}
};

