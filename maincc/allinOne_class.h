#pragma once
#include <iostream>
#include <string>
using namespace std;

class AllinOne_class {
	string buildingName, diet;

public:
	AllinOne_class() {
		buildingName = this->buildingName;
		diet = this->diet;
	}

	string get_buildingName() {
		return buildingName;
	}

	string get_diet() {
		return diet;
	}

	friend void diningManagement();
	friend void menuPlanManagement();
	friend void otherMenuPlanManagement();
	friend void show_orders();
	friend int main();
};

AllinOne_class allinOne_class;