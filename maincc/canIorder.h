#pragma once
#include <iostream>
#include <string>
#include "file_com_pragmaonce_mysql.h"
#include "timeConverter.h"
#include "getCurrentHour.h"
#include "getCurrentMinute.h"
#include "getName_fromTable.h"

using namespace std;

//int qstateisFoodBuildingClosedYet;

bool canIorder(string FoodBuildingNameFormated, string mealName) {
	//Stablishing the connection to mysql database
	MYSQL* conn;
	//MYSQL_ROW row;
	//MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

	if (conn) {
		//getting current time first
		string minutoAgora, tempMin = getCurrentMinute();
		if (stoi(tempMin) < 10)
			minutoAgora = "0" + tempMin;
		else minutoAgora = tempMin;
		int TimeNowIntForm = stoi(getCurrentHour() + minutoAgora);

		//start time and end time
		string mealStartTimeAmPm = getName_fromTable(FoodBuildingNameFormated + "MealsTimeAndPrice", "startTime", "meal", mealName), mealEndTimeAmPm = getName_fromTable(FoodBuildingNameFormated + "MealsTimeAndPrice", "endTime", "meal", mealName);
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
	else puts("Connection to DataBase has failed");
}