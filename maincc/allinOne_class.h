#pragma once
#include <iostream>
#include <string>
using namespace std;

class AllinOne_class {
	string buildingName, mealType;

public:
	AllinOne_class() {
		buildingName = this->buildingName;
		mealType = this->mealType;
	}

	string get_buildingName() {
		return buildingName;
	}

	string get_mealType() {
		return mealType;
	}

	friend void diningManagement();
	friend void menuPlanManagement();
	friend void otherMenuPlanManagement();
};

AllinOne_class allinOne_class;