#pragma once
#include <iostream>
#include <string>
#include "file_com_pragmaonce_mysql.h"
#include "timeConverter.h"
#include "getCurrentHour.h"
#include "getCurrentMinute.h"
#include "getName_fromTable.h"
#include "isFoodBuildingOpenYet.h"
#include "isFoodBuildingClosedYet.h"

using namespace std;

int qstatecanIorder;

bool canIorder(string FoodBuildingNameFormated, string mealName) {
	//Stablishing the connection to mysql database
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

	if (conn) {
		//getting current time first
		string minutoAgora, tempMin = getCurrentMinute();
		if (stoi(tempMin) < 10)
			minutoAgora = "0" + tempMin;
		else minutoAgora = tempMin;
		int TimeNowIntForm = stoi(getCurrentHour() + minutoAgora);

		if (mealName != "Other") {
			//start time and end time
			string mealStartTimeAmPm = getName_fromTable(FoodBuildingNameFormated + "MealsTimeAndPrice", "startTime", "meal", mealName);
			string mealEndTimeAmPm = getName_fromTable(FoodBuildingNameFormated + "MealsTimeAndPrice", "endTime", "meal", mealName);

			if (mealStartTimeAmPm != "none" && mealEndTimeAmPm != "none") {
				string mealStartTimeMilitar = timeConverter(mealStartTimeAmPm), mealEndTimeMilitar = timeConverter(mealEndTimeAmPm);

				string tempString1 = mealStartTimeMilitar, tempString2 = mealEndTimeMilitar;

				int i = tempString1.find(':');
				tempString1.erase(i, 1);
				mealStartTimeMilitar = tempString1;

				int j = tempString2.find(':');
				tempString2.erase(j, 1);
				mealEndTimeMilitar = tempString2;

				//compare
				if (TimeNowIntForm >= stoi(mealStartTimeMilitar) && TimeNowIntForm < stoi(mealEndTimeMilitar))
					return true;
				else return false;
			}
			else return false;
		}
		else if (mealName == "Other" && tableExists(FoodBuildingNameFormated + "MealsTimeAndPrice") == true) {//IN CASE THERE IS A MENU PLAN TABLE, BUT STUDENT DOESNT WANT ANY MEALS
			if (canIorder(myOrder.get_selectedBuilding(), "Breakfast") == true || canIorder(myOrder.get_selectedBuilding(), "Brunch") == true || canIorder(myOrder.get_selectedBuilding(), "Lunch") == true || canIorder(myOrder.get_selectedBuilding(), "Dinner") == true) {
				return true;
			}
			else return false;
		}
		else if (mealName == "Other" && tableExists(FoodBuildingNameFormated + "MealsTimeAndPrice") == false) {//IN CASE THERE IS NOT A MENU PLAN TABLE, BUT STUDENT DOESNT WANT ANY MEALS
			//get dayName
			string dayName;
			string queryDayName = "SELECT DAYNAME(NOW())";
			const char* qDayName = queryDayName.c_str();
			qstatecanIorder = mysql_query(conn, qDayName);
			if (!qstatecanIorder) {
				res = mysql_store_result(conn);
				row = mysql_fetch_row(res);
				dayName = row[0];
			}
			else cout << "Query failed: " << mysql_error(conn) << "\n";

			//get currentTime
			//getting current time first
			string minutoAgora, tempMin = getCurrentMinute();
			if (stoi(tempMin) < 10)
				minutoAgora = "0" + tempMin;
			else minutoAgora = tempMin;
			string amPmTimeNowIs = timeConverter(getCurrentHour() + ":" + minutoAgora);

			if (isFoodBuildingOpenYet(FoodBuildingNameFormated, dayName, amPmTimeNowIs) == true && isFoodBuildingClosedYet(FoodBuildingNameFormated, dayName, amPmTimeNowIs) == false)
				return true;
			else return false;
		}
	}
	else puts("Connection to DataBase has failed");
}