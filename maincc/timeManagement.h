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
					string startampm, endampm;
					if (updateOption == "1") {
						//Update Start time
					setStartTime:
						//get endhr from DB so it sets the right boundaries every time
						string starthrChoice, starthr, endhr, endTime = getName_fromTable(buildingName + "MealsTimeAndPrice", "endTime", "meal", mealName);
						if (endTime == "none")
							endhr = "none";
						else {
							int i = endTime.find(':');
							for (int j = 0; j < i; j++)
								endhr += endTime[j];
						}

						cout << "*Select Hour\n";
						if (endhr != "none") {
							cout << "n- None\n";
							if (stoi(endhr) == 12) {
								for (int i = 0; i < 12; i++)
									cout << i << "- " << i << "\n";
							}
							else if (stoi(endhr) != 12) {
								for (int i = 0; i <= 12; i++) {
									if (i == stoi(endhr))
										continue;
									else cout << i << "- " << i << "\n";
								}
							}
						}
						else {
							cout << "n- None\n";
							for (int i = 0; i <= 12; i++)
								cout << i << "- " << i << "\n";
						}

						cout << "Please, enter an option: ";
						cin >> starthrChoice;

						if (isdigit(starthrChoice[0]) != 0)
							starthr = starthrChoice;
						else if (starthrChoice == "n")
							starthr = "none";

						//BEFORE UPDATE IN DB, CHECK IF THE TIME IS AFTER OPENINGTIME AND BEFORE CLOSING TIME!!!
						if (starthr != "none") {
							cout << "*Select Minute\n";
							for (int i = 0; i <= 59; i += 5) //CURIOUS: why are the minutes in time schedules usually multiples of 5???
								cout << i << "- " << i << "\n";
							cout << "Please, enter an option: ";
							int min;
							cin >> min;

							cout << "* Select an option\n";
							cout << "1- AM\n";
							if (starthr != "0")
								cout << "2- PM\n";
							cout << "b- Back\n";
							cout << "Please, enter an option: ";
							string ampmChoice;
							cin >> ampmChoice;
							if (ampmChoice == "1")
								startampm = "AM";
							else if (ampmChoice == "2")
								startampm = "PM";
							else if (ampmChoice == "b")
								goto setStartTime;

							string minString;
							if (min < 10)
								minString = "0" + to_string(min);
							else minString = to_string(min);

							if (isFoodBuildingOpenYet(buildingName, "Monday", starthr + ":" + minString + " " + startampm) == true && isFoodBuildingClosedYet(buildingName, "Monday", starthr + ":" + minString + " " + startampm) == false && mealName != "Brunch") {
								//Update Start time in DB
								string newStartTime = starthr + ":" + minString + " " + startampm;
								string queryUpdateStartTime = "UPDATE " + buildingName + "MealsTimeAndPrice SET startTime = '" + newStartTime + "' WHERE meal = '" + mealName + "'";
								const char* qUpdateStartTime = queryUpdateStartTime.c_str();
								qstateTimeManagement = mysql_query(conn, qUpdateStartTime);
								if (qstateTimeManagement)
									cout << "Query failed: " << mysql_error(conn) << "\n";
							}
							else if (isFoodBuildingOpenYet(buildingName, "Sunday", starthr + ":" + minString + " " + startampm) == true && isFoodBuildingClosedYet(buildingName, "Sunday", starthr + ":" + minString + " " + startampm) == false && mealName == "Brunch") {
								//Update Start time in DB
								string newStartTime = starthr + ":" + minString + " " + startampm;
								string queryUpdateStartTime = "UPDATE " + buildingName + "MealsTimeAndPrice SET startTime = '" + newStartTime + "' WHERE meal = '" + mealName + "'";
								const char* qUpdateStartTime = queryUpdateStartTime.c_str();
								qstateTimeManagement = mysql_query(conn, qUpdateStartTime);
								if (qstateTimeManagement)
									cout << "Query failed: " << mysql_error(conn) << "\n";
							}
							else cout << "* Invalid!\n";
						}
						else {
							string queryUpdateStartTime = "UPDATE " + buildingName + "MealsTimeAndPrice SET startTime = '" + starthr + "' WHERE meal = '" + mealName + "'";
							const char* qUpdateStartTime = queryUpdateStartTime.c_str();
							qstateTimeManagement = mysql_query(conn, qUpdateStartTime);
							if (qstateTimeManagement)
								cout << "Query failed: " << mysql_error(conn) << "\n";
						}

						goto selectedMeal;
					}
					else if (updateOption == "2") {
						//Update End time
					setEndTime:
						//get starthr from DB so it sets the right boundaries every time
						string endhrChoice, endhr, starthr, startTime = getName_fromTable(buildingName + "MealsTimeAndPrice", "startTime", "meal", mealName);
						if (startTime == "none")
							starthr = "none";
						else {
							int i = startTime.find(':');
							for (int j = 0; j < i; j++)
								starthr += startTime[j];
						}

						//only cout hours different from the start hour
						cout << "*Select Hour\n";
						if (starthr != "none") {
							cout << "n- None\n";
							if (stoi(starthr) == 12) {
								for (int i = 0; i < 12; i++)
									cout << i << "- " << i << "\n";
							}
							else if (stoi(starthr) != 12) {
								for (int i = 0; i <= 12; i++) {
									if (i == stoi(starthr))
										continue;
									else cout << i << "- " << i << "\n";
								}
							}
						}
						else {
							cout << "n- None\n";
							for (int i = 0; i <= 12; i++)
								cout << i << "- " << i << "\n";
						}

						cout << "Please, enter an option: ";
						cin >> endhrChoice;

						if (isdigit(endhrChoice[0]) != 0)
							endhr = endhrChoice;
						else if (endhrChoice == "n")
							endhr = "none";

						//BEFORE UPDATE IN DB, CHECK IF THE TIME IS BEFORE CLOSINGTIME  AND AFTER OPENING TIME!!!
						if (endhr != "none") {
							cout << "*Select Minute\n";
							for (int i = 0; i <= 59; i += 5)
								cout << i << "- " << i << "\n";
							cout << "Please, enter an option: ";
							int min;
							cin >> min;

							cout << "* Select an option\n";
							cout << "1- AM\n";
							if (endhr != "0")
								cout << "2- PM\n";
							cout << "b- Back\n";
							cout << "Please, enter an option: ";
							string ampmChoice;
							cin >> ampmChoice;
							if (ampmChoice == "1")
								endampm = "AM";
							else if (ampmChoice == "2")
								endampm = "PM";
							else if (ampmChoice == "b")
								goto setEndTime;

							string minString;
							if (min < 10)
								minString = "0" + to_string(min);
							else minString = to_string(min);

							if (isFoodBuildingOpenYet(buildingName, "Monday", starthr + ":" + minString + " " + startampm) == true && isFoodBuildingClosedYet(buildingName, "Monday", endhr + ":" + minString + " " + endampm) == false && mealName != "Brunch") {
								//Update End time in DB
								string newEndTime = endhr + ":" + minString + " " + endampm;
								string queryUpdateEndTime = "UPDATE " + buildingName + "MealsTimeAndPrice SET endTime = '" + newEndTime + "' WHERE meal = '" + mealName + "'";
								const char* qUpdateEndTime = queryUpdateEndTime.c_str();
								qstateTimeManagement = mysql_query(conn, qUpdateEndTime);
								if (qstateTimeManagement)
									cout << "Query failed: " << mysql_error(conn) << "\n";
							}
							else if (isFoodBuildingOpenYet(buildingName, "Sunday", starthr + ":" + minString + " " + startampm) == true && isFoodBuildingClosedYet(buildingName, "Sunday", endhr + ":" + minString + " " + endampm) == false && mealName == "Brunch") {
								//Update End time in DB
								string newEndTime = endhr + ":" + minString + " " + endampm;
								string queryUpdateEndTime = "UPDATE " + buildingName + "MealsTimeAndPrice SET endTime = '" + newEndTime + "' WHERE meal = '" + mealName + "'";
								const char* qUpdateEndTime = queryUpdateEndTime.c_str();
								qstateTimeManagement = mysql_query(conn, qUpdateEndTime);
								if (qstateTimeManagement)
									cout << "Query failed: " << mysql_error(conn) << "\n";
							}
							else cout << "* Invalid!\n";
						}
						else {
							string queryUpdateEndTime = "UPDATE " + buildingName + "MealsTimeAndPrice SET endTime = '" + endhr + "' WHERE meal = '" + mealName + "'";
							const char* qUpdateEndTime = queryUpdateEndTime.c_str();
							qstateTimeManagement = mysql_query(conn, qUpdateEndTime);
							if (qstateTimeManagement)
								cout << "Query failed: " << mysql_error(conn) << "\n";
						}

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
				 buildingName = formatName(buildingName);
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
					 string openinghrChoice, openinghr;
					 int openingmin;
					 cout << "*Select Hour\n";
					 cout << "n- None\n";
					 for (int i = 0; i <= 12; i++)
						 cout << i << "- " << i << "\n";
					 cout << "Please, enter an option: ";
					 cin >> openinghrChoice;
					 if (openinghrChoice == "n")
						 openinghr = "none";
					 else openinghr = openinghrChoice;

					 if (openinghr != "none") {
						 cout << "*Select Minute\n";
						 for (int i = 0; i <= 59; i += 5) //CURIOUS: why are the minutes in time schedules usually multiples of 5???
							 cout << i << "- " << i << "\n";
						 cout << "Please, enter an option: ";
						 cin >> openingmin;

						 cout << "* Select an option\n";
						 cout << "1- AM\n";
						 if (openinghr != "0")
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
						 string openingminString;
						 if (openingmin < 10)
							 openingminString = "0" + to_string(openingmin);
						 else openingminString = to_string(openingmin);
						 string newOpeningTime = openinghr + ":" + openingminString + " " + openingampm;
						 string queryUpdateOpeningTime = "UPDATE " + buildingName + "WorkingTimesTable SET openingTime = '" + newOpeningTime + "' WHERE dayName = '" + dayName + "'";
						 const char* qUpdateOpeningTime = queryUpdateOpeningTime.c_str();
						 qstateManagement = mysql_query(conn, qUpdateOpeningTime);
						 if (qstateManagement)
							 cout << "Query failed: " << mysql_error(conn) << "\n";
					 }
					 else {
						 string queryUpdateOpeningTime = "UPDATE " + buildingName + "WorkingTimesTable SET openingTime = '" + openinghr + "' WHERE dayName = '" + dayName + "'";
						 const char* qUpdateOpeningTime = queryUpdateOpeningTime.c_str();
						 qstateManagement = mysql_query(conn, qUpdateOpeningTime);
						 if (qstateManagement)
							 cout << "Query failed: " << mysql_error(conn) << "\n";
					 }

					 //closingTime
				 setClosingTime:
					 cout << "** Closing Time **\n";
					 //Update closing time
					 string closinghrChoice, closinghr;
					 int closingmin;
					 cout << "*Select Hour\n";
					 cout << "n- None\n";
					 for (int i = 0; i <= 12; i++)
						 cout << i << "- " << i << "\n";
					 cout << "Please, enter an option: ";
					 cin >> closinghrChoice;
					 if (closinghrChoice == "n")
						 closinghr = "none";
					 else closinghr = closinghrChoice;

					 if (closinghr != "none") {
						 cout << "*Select Minute\n";
						 for (int i = 0; i <= 59; i += 5) //CURIOUS: why are the minutes in time schedules usually multiples of 5???
							 cout << i << "- " << i << "\n";
						 cout << "Please, enter an option: ";
						 cin >> closingmin;

						 cout << "* Select an option\n";
						 cout << "1- AM\n";
						 if (closinghr != "0")
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
						 string closingminString;
						 if (closingmin < 10)
							 closingminString = "0" + to_string(closingmin);
						 else closingminString = to_string(closingmin);
						 string newClosingTime = closinghr + ":" + closingminString + " " + closingampm;
						 string queryUpdateClosingTime = "UPDATE " + buildingName + "WorkingTimesTable SET closingTime = '" + newClosingTime + "' WHERE dayName = '" + dayName + "'";
						 const char* qUpdateClosingTime = queryUpdateClosingTime.c_str();
						 qstateManagement = mysql_query(conn, qUpdateClosingTime);
						 if (qstateManagement)
							 cout << "Query failed: " << mysql_error(conn) << "\n";
					 }
					 else {
						 string queryUpdateClosingTime = "UPDATE " + buildingName + "WorkingTimesTable SET closingTime = '" + closinghr + "' WHERE dayName = '" + dayName + "'";
						 const char* qUpdateClosingTime = queryUpdateClosingTime.c_str();
						 qstateManagement = mysql_query(conn, qUpdateClosingTime);
						 if (qstateManagement)
							 cout << "Query failed: " << mysql_error(conn) << "\n";
					 }

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