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
	//MYSQL_ROW row;
	//MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

	if (conn) {
	theBuildings:
		cout << "* Select a building \n";
		//listing the buildings in the foodBuildingsTable
		if (tableExists("foodBuildingsTable") == true)
			listarCoisas("foodBuildingID", "foodBuildingName", "foodBuildingsTable");
		else cout << "No building!\n";
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
			if(tableExists(buildingName + "MealsTimeAndPrice")==true)
				listarCoisas("mealID", "meal", buildingName + "MealsTimeAndPrice");
			else cout << "No meal!\n";
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
					setStartTime:
					//Update Start time
					int hr, min;
					cout << "*Select Hour\n";
					for (int i = 0; i <= 12; i++)
						cout << i << "- " << i << "\n";
					cout << "Please, enter an option: ";
					cin >> hr;
					
					cout << "*Select Minute\n";
					for (int i = 0; i <= 59; i++) //CURIOUS: why are the minutes in time schedules usually multiples of 5???
						cout << i << "- " << i << "\n";
					cout << "Please, enter an option: ";
					cin >> min;

					cout << "* Select an option\n";
					cout << "1- AM\n";
					cout << "2- PM\n";
					cout << "b- Back\n";
					cout << "Please, enter an option: ";
					string ampmChoice, ampm;
					cin >> ampmChoice;
					if (ampmChoice == "1")
						ampm = "AM";
					else if (ampmChoice == "2")
						ampm = "PM";
					else if (ampmChoice == "b")
						goto setStartTime;

					//Update Start time in DB
					string hrString = to_string(hr), minString;
					if (min < 10)
						minString = "0" + to_string(min);
					else minString = to_string(min);
					string newStartTime = hrString + ":" + minString + " " + ampm;
					string queryUpdateStartTime = "UPDATE " + buildingName + "MealsTimeAndPrice SET startTime = '" + newStartTime + "' WHERE meal = '" + mealName + "'";
					const char* qUpdateStartTime = queryUpdateStartTime.c_str();
					qstatemealsTimePeriodManagement = mysql_query(conn, qUpdateStartTime);
					if (qstatemealsTimePeriodManagement)
						cout << "Query failed: " << mysql_error(conn) << "\n";

					goto selectedMeal;
				}
				else if (updateOption == "2") {
					setEndTime:
					//Update End time
					int hr, min;
					cout << "*Select Hour\n";
					for (int i = 0; i <= 12; i++)
						cout << i << "- " << i << "\n";
					cout << "Please, enter an option: ";
					cin >> hr;

					cout << "*Select Minute\n";
					for (int i = 0; i <= 59; i++) //CURIOUS: why are the minutes in time schedules usually multiples of 5???
						cout << i << "- " << i << "\n";
					cout << "Please, enter an option: ";
					cin >> min;

					cout << "* Select an option\n";
					cout << "1- AM\n";
					cout << "2- PM\n";
					cout << "b- Back\n";
					cout << "Please, enter an option: ";
					string ampmChoice, ampm;
					cin >> ampmChoice;
					if (ampmChoice == "1")
						ampm = "AM";
					else if (ampmChoice == "2")
						ampm = "PM";
					else if (ampmChoice == "b")
						goto setEndTime;

					//Update End time in DB
					string hrString = to_string(hr), minString;
					if (min < 10)
						minString = "0" + to_string(min);
					else minString = to_string(min);
					string newEndTime = hrString + ":" + minString + " " + ampm;
					string queryUpdateEndTime = "UPDATE " + buildingName + "MealsTimeAndPrice SET endTime = '" + newEndTime + "' WHERE meal = '" + mealName + "'";
					const char* qUpdateEndTime = queryUpdateEndTime.c_str();
					qstatemealsTimePeriodManagement = mysql_query(conn, qUpdateEndTime);
					if (qstatemealsTimePeriodManagement)
						cout << "Query failed: " << mysql_error(conn) << "\n";

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