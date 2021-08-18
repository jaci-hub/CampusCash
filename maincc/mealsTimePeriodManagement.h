#pragma once
#include <iostream>
#include <string>
#include "diningManagement.h"
#include "deliveryManagement.h"
#include "feesManagement.h"
using namespace std;

int qstatemealsTimePeriodManagement;

void mealsTimePeriodManagement() {
	//Stablishing the connection to mysql database
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

	if (conn) {
		theBuildings:
		cout << "* Select a building \n";
		//listing the buildings in the foodBuildingsTable
		listarCoisas("foodBuildingID", "foodBuildingName", "foodBuildingsTable");
		cout << "e- EXIT\n";
		cout << "Please, enter an option: ";
		string casaSelected;
		cin >> casaSelected;

		if (isdigit(casaSelected[0]) != 0) {
		theMeals:
			string buildingName = getName_fromTable("foodBuildingsTable", "foodBuildingName", "foodBuildingID", casaSelected);
			buildingName = formatName(buildingName);
			cout << "* Select meal \n";
			//listing the meals in the MealsTimeAndPrice
			listarCoisas("mealID", "meal", buildingName + "MealsTimeAndPrice");
			cout << "b- Back\n";
			cout << "Please, enter an option: ";
			string mealSelected;
			cin >> mealSelected;

			if (isdigit(mealSelected[0]) != 0) {
				selectedMeal:
				string mealName = getName_fromTable(buildingName + "MealsTimeAndPrice", "meal", "mealID", mealSelected);

				//***Display Start and End times//
				//start time
				string startTime = getName_fromTable(buildingName + "MealsTimeAndPrice", "startTime", "meal", mealName);

				//end time
				string endTime = getName_fromTable(buildingName + "MealsTimeAndPrice", "endTime", "meal", mealName);
				
				cout << "** " << mealName << " Time Period**\n";
				cout << "*Start: " << startTime << "\n";
				cout << "*End: " << endTime << "\n\n";
				cout << "1- Update Start time\n";
				cout << "2- Update End time\n";
				cout << "b- Back\n";
				cout << "Please, enter an option: ";
				string updateOption;
				cin >> updateOption;

				if (updateOption == "1") {
					//Update Start time


					goto selectedMeal;
				}
				else if (updateOption == "2") {
					//Update End time


					goto selectedMeal;
				}
				else if (updateOption == "b")
					goto theMeals;
			}
			else if (mealSelected == "b")
				goto theBuildings;
		}
		else if (casaSelected == "e")
			goto mealsTimePeriodManagementEnd;
	}
	else puts("Connection to DataBase has failed");

mealsTimePeriodManagementEnd:
	cout << "";
}