#pragma once
#include <iostream>
#include <string>
#include "diningManagement.h"
#include "deliveryManagement.h"
#include "feesManagement.h"
#include "isFoodBuildingOpenYet.h"
#include "isFoodBuildingClosedYet.h"
using namespace std;

int qstateTimeManagement;

void timeManagement() {
	//Stablishing the connection to mysql database
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

	if (conn) {
		principio:
		cout << "* Select an option \n";
		cout << "1- Working hours\n";
		cout << "2- Meal hours\n";
		cout << "e- EXIT\n";
		cout << "Please, enter an option: ";
		string firstChoice;
		cin >> firstChoice;
		if (firstChoice == "2") {
		theBuildings:
			cout << "* Meals hours at: \n";
			//listing the buildings in the foodBuildingsTable
			if (tableExists("foodBuildingsTable") == true)
				listarCoisas("foodBuildingID", "foodBuildingName", "foodBuildingsTable");
			else cout << "No building!\n";
			cout << "b- Back\n";
			cout << "Please, enter an option: ";
			string casaSelected;
			cin >> casaSelected;

			if (isdigit(casaSelected[0]) != 0) {
			theMeals:
				string buildingName = getName_fromTable("foodBuildingsTable", "foodBuildingName", "foodBuildingID", casaSelected);
				buildingName = formatName(buildingName);
				cout << "* Select meal \n";
				//listing the meals in the MealsTimeAndPrice
				if (tableExists(buildingName + "MealsTimeAndPrice") == true)
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

						//BEFORE UPDATE IN DB, CHECK IF THE TIME IS AFTER OPENINGTIME!!!
						string hrString = to_string(hr), minString;
						if (min < 10)
							minString = "0" + to_string(min);
						else minString = to_string(min);

						if (isFoodBuildingOpenYet(buildingName, hrString + ":" + minString + " " + ampm) == true) {
							//Update Start time in DB
							string newStartTime = hrString + ":" + minString + " " + ampm;
							string queryUpdateStartTime = "UPDATE " + buildingName + "MealsTimeAndPrice SET startTime = '" + newStartTime + "' WHERE meal = '" + mealName + "'";
							const char* qUpdateStartTime = queryUpdateStartTime.c_str();
							qstateTimeManagement = mysql_query(conn, qUpdateStartTime);
							if (qstateTimeManagement)
								cout << "Query failed: " << mysql_error(conn) << "\n";
						}
						else cout << "* Building not open yet at that time!\n";

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

						//BEFORE UPDATE IN DB, CHECK IF THE TIME IS BEFORE CLOSINGTIME!!!
						string hrString = to_string(hr), minString;
						if (min < 10)
							minString = "0" + to_string(min);
						else minString = to_string(min);

						if (isFoodBuildingClosedYet(buildingName, hrString + ":" + minString + " " + ampm) == false) {
							//Update Start time in DB
							string newEndTime = hrString + ":" + minString + " " + ampm;
							string queryUpdateEndTime = "UPDATE " + buildingName + "MealsTimeAndPrice SET startTime = '" + newEndTime + "' WHERE meal = '" + mealName + "'";
							const char* qUpdateEndTime = queryUpdateEndTime.c_str();
							qstateTimeManagement = mysql_query(conn, qUpdateEndTime);
							if (qstateTimeManagement)
								cout << "Query failed: " << mysql_error(conn) << "\n";
						}
						else cout << "* Building already closed at that time!\n";

						goto selectedMeal;
					}
					else if (updateOption == "b")
						goto theMeals;
				}
				else if (mealSelected == "b")
					goto theBuildings;
			}
			else if (casaSelected == "b")
				goto principio;
		}

		else if (firstChoice == "1") {
			listarEdificios:
			cout << "* Working hours at: \n";
			//listing the buildings in the foodBuildingsTable
			if (tableExists("foodBuildingsTable") == true)
				listarCoisas("foodBuildingID", "foodBuildingName", "foodBuildingsTable");
			else cout << "No building!\n";
			cout << "b- Back\n";
			cout << "Please, enter an option: ";
			string edificioSelected;
			cin >> edificioSelected;
			 if (edificioSelected == "b")
				goto principio;
			 if (isdigit(edificioSelected[0]) != 0) {
				 edificioSelecionado:
				 string buildingName = getName_fromTable("foodBuildingsTable", "foodBuildingName", "foodBuildingID", edificioSelected);
				 
				 //***Display Opening and Closing times by day//
				 cout << "** " << buildingName << " working hours**\n";
				 cout << "* Select a day to update hours\n";
				 //listar dias: openingTime - closingTime
				 string querySelectTimes = "SELECT dayName, openingTime, closingTime FROM " + buildingName + "WorkingTimesTable";
				 const char* qSelectTimes = querySelectTimes.c_str();
				 qstateTimeManagement = mysql_query(conn, qSelectTimes);
				 if (!qstateTimeManagement) {
					 res = mysql_store_result(conn);
					 int i = 1;
					 while (row = mysql_fetch_row(res)) {
						 cout << i << "- " << row[0] << ": " << row[1] << " - " << row[2] << "\n";
						 i++;
					 }
				 }
				 else cout << "Query failed: " << mysql_error(conn) << "\n";

				 cout << "b- Back\n";
				 cout << "Please, enter an option: ";
				 string updateOption;
				 cin >> updateOption;
				 if (updateOption == "b")
					 goto listarEdificios;
				 else if (isdigit(updateOption[0]) != 0) {
					 //setting numbers to days
					 string dayName;
					 if (updateOption == "1")
						 dayName = "Sunday";
					 else if (updateOption == "2")
						 dayName = "Monday";
					 else if (updateOption == "3")
						 dayName = "Tuesday";
					 else if (updateOption == "4")
						 dayName = "Wednesday";
					 else if (updateOption == "5")
						 dayName = "Thursday";
					 else if (updateOption == "6")
						 dayName = "Friday";
					 else if (updateOption == "7")
						 dayName = "Saturday";

					 //openingTime
				 setOpeningTime:
					 cout << "** Opening Time **\n";
					 //Update opening time
					 int openinghr, openingmin;
					 cout << "*Select Hour\n";
					 for (int i = 0; i <= 12; i++)
						 cout << i << "- " << i << "\n";
					 cout << "Please, enter an option: ";
					 cin >> openinghr;

					 cout << "*Select Minute\n";
					 for (int i = 0; i <= 59; i++) //CURIOUS: why are the minutes in time schedules usually multiples of 5???
						 cout << i << "- " << i << "\n";
					 cout << "Please, enter an option: ";
					 cin >> openingmin;

					 cout << "* Select an option\n";
					 cout << "1- AM\n";
					 cout << "2- PM\n";
					 cout << "b- Back\n";
					 cout << "Please, enter an option: ";
					 string openingampmChoice, openingampm;
					 cin >> openingampmChoice;
					 if (openingampmChoice == "1")
						 openingampm = "AM";
					 else if (openingampmChoice == "2")
						 openingampm = "PM";
					 else if (openingampmChoice == "b")
						 goto setOpeningTime;

					 //Update Opening time in DB
					 string openinghrString = to_string(openinghr), openingminString;
					 if (openingmin < 10)
						 openingminString = "0" + to_string(openingmin);
					 else openingminString = to_string(openingmin);
					 string newOpeningTime = openinghrString + ":" + openingminString + " " + openingampm;
					 string queryUpdateOpeningTime = "UPDATE " + buildingName + "WorkingTimesTable SET openingTime = '" + newOpeningTime + "' WHERE dayName = '" + dayName + "'";
					 const char* qUpdateOpeningTime = queryUpdateOpeningTime.c_str();
					 qstateManagement = mysql_query(conn, qUpdateOpeningTime);
					 if (qstateManagement)
						 cout << "Query failed: " << mysql_error(conn) << "\n";

					 //closingTime
				 setClosingTime:
					 cout << "** Closing Time **\n";
					 //Update closing time
					 int closinghr, closingmin;
					 cout << "*Select Hour\n";
					 for (int i = 0; i <= 12; i++)
						 cout << i << "- " << i << "\n";
					 cout << "Please, enter an option: ";
					 cin >> closinghr;

					 cout << "*Select Minute\n";
					 for (int i = 0; i <= 59; i++) //CURIOUS: why are the minutes in time schedules usually multiples of 5???
						 cout << i << "- " << i << "\n";
					 cout << "Please, enter an option: ";
					 cin >> closingmin;

					 cout << "* Select an option\n";
					 cout << "1- AM\n";
					 cout << "2- PM\n";
					 cout << "b- Back\n";
					 cout << "Please, enter an option: ";
					 string closingampmChoice, closingampm;
					 cin >> closingampmChoice;
					 if (closingampmChoice == "1")
						 closingampm = "AM";
					 else if (closingampmChoice == "2")
						 closingampm = "PM";
					 else if (closingampmChoice == "b")
						 goto setClosingTime;

					 //Update Closing time in DB
					 string closinghrString = to_string(closinghr), closingminString;
					 if (closingmin < 10)
						 closingminString = "0" + to_string(closingmin);
					 else closingminString = to_string(closingmin);
					 string newClosingTime = closinghrString + ":" + closingminString + " " + closingampm;
					 string queryUpdateClosingTime = "UPDATE " + buildingName + "WorkingTimesTable SET closingTime = '" + newClosingTime + "' WHERE dayName = '" + dayName + "'";
					 const char* qUpdateClosingTime = queryUpdateClosingTime.c_str();
					 qstateManagement = mysql_query(conn, qUpdateClosingTime);
					 if (qstateManagement)
						 cout << "Query failed: " << mysql_error(conn) << "\n";

					 goto edificioSelecionado;
				 }
			 }
		}

		else if (firstChoice == "e")
			goto TimeManagementEnd;
	}
	else puts("Connection to DataBase has failed");

TimeManagementEnd:
	cout << "";
}