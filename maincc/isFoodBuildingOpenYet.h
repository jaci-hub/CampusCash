#pragma once
#include <iostream>
#include <string>
#include "file_com_pragmaonce_mysql.h"
#include "timeConverter.h"

using namespace std;

int qstateisFoodBuildingOpenYet;

bool isFoodBuildingOpenYet(string foodBuildingNameFormated, string aDay, string AnOpeningTime) {
	//Stablishing the connection to mysql database
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

	if (conn) {
		//get buildingOpeningTime
		string buildingOpeningTime;
		string queryGettingbuildingOpeningTime = "SELECT openingTime FROM " + foodBuildingNameFormated + "WorkingTimesTable WHERE dayName = '" + aDay + "'";
		const char* qGettingbuildingOpeningTime = queryGettingbuildingOpeningTime.c_str();
		qstateisFoodBuildingOpenYet = mysql_query(conn, qGettingbuildingOpeningTime);
		if (!qstateisFoodBuildingOpenYet) {
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			buildingOpeningTime = row[0];
		}
		else cout << "Query failed: " << mysql_error(conn) << "\n";

		if (buildingOpeningTime != "none") {
			//take the colon away from buildingOpeningTime (now it can be turned into integer)
			string tempString = timeConverter(buildingOpeningTime);
			int i = tempString.find(':');
			tempString.erase(i, 1);
			buildingOpeningTime = tempString;

			//take the colon away from given time (now it can be turned into integer)
			string givenTime;
			string tempString1 = timeConverter(AnOpeningTime);
			int j = tempString1.find(':');
			tempString1.erase(j, 1);
			givenTime = tempString1;

			if (stoi(givenTime) >= stoi(buildingOpeningTime))
				return true;
			else return false;
		}
		else return false;
	}
	else puts("Connection to DataBase has failed");
}