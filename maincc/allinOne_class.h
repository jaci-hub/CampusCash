#pragma once
#include <iostream>
#include <string>
using namespace std;

class AllinOne_class {
	string buildingName;

public:
	AllinOne_class() {
		buildingName = this->buildingName;
	}

	string get_buildingName() {
		return buildingName;
	}

	friend void diningManagement();
};

AllinOne_class allinOne_class;