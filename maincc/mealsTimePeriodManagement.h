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
			cout << "1- Breakfast\n";
			cout << "2- Brunch\n";
			cout << "3- Lunch\n";
			cout << "4- Diner\n";
			cout << "b- Back\n";
			cout << "Please, enter an option: ";
			string mealSelected;
			cin >> mealSelected;

			if (isdigit(mealSelected[0]) != 0) {
				selectedMeal:
				string mealName;
				if (mealSelected == "1")
					mealName = "Breakfast";
				else if (mealSelected == "2") 
					mealName = "Brunch";
				else if (mealSelected == "3") 
					mealName = "Lunch";
				else if (mealSelected == "4") 
					mealName = "Diner";

				//***Display Start and End times//
				//start time
				string startTime;
				string queryGettingStartTime = "SELECT startTime FROM " + buildingName + "MealsTimeAndPrice WHERE meal = '" + mealName + "'";
				const char* qGettingStartTime = queryGettingStartTime.c_str();
				qstatemealsTimePeriodManagement = mysql_query(conn, qGettingStartTime);
				if (!qstatemealsTimePeriodManagement) {
					res = mysql_store_result(conn);
					row = mysql_fetch_row(res);
					startTime = row[0];
				}
				else cout << "Query failed: " << mysql_error(conn) << "\n";

				//end time
				string endTime;
				string queryGettingEndTime = "SELECT endTime FROM " + buildingName + "MealsTimeAndPrice WHERE meal = '" + mealName + "'";
				const char* qGettingEndTime = queryGettingEndTime.c_str();
				qstatemealsTimePeriodManagement = mysql_query(conn, qGettingEndTime);
				if (!qstatemealsTimePeriodManagement) {
					res = mysql_store_result(conn);
					row = mysql_fetch_row(res);
					endTime = row[0];
				}
				else cout << "Query failed: " << mysql_error(conn) << "\n";

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