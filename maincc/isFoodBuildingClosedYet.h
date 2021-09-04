#pragma once
#include <iostream>
#include <string>
#include "file_com_pragmaonce_mysql.h"
#include "timeConverter.h"

using namespace std;

int qstateisFoodBuildingClosedYet;

bool isFoodBuildingClosedYet(string foodBuildingNameFormated, string aClosingTime) {
	//Stablishing the connection to mysql database
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

	if (conn) {
		//get buildingClosingTime
		string buildingClosingTime;
		string queryGettingbuildingClosingTime = "SELECT closingTime FROM " + foodBuildingNameFormated + "WorkingTimesTable";
		const char* qGettingbuildingClosingTime = queryGettingbuildingClosingTime.c_str();
		qstateisFoodBuildingClosedYet = mysql_query(conn, qGettingbuildingClosingTime);
		if (!qstateisFoodBuildingClosedYet) {
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			buildingClosingTime = row[0];
		}
		else cout << "Query failed: " << mysql_error(conn) << "\n";

		//take the colon away from buildingClosingTime (now it can be turned into integer)
		string tempString = timeConverter(buildingClosingTime);
		int i = tempString.find(':');
		tempString.erase(i, 1);
		buildingClosingTime = tempString;
		
		//take the colon away from given time (now it can be turned into integer)
		string givenTime;
		string tempString1 = timeConverter(aClosingTime);
		int j = tempString1.find(':');
		tempString1.erase(j, 1);
		givenTime = tempString1;

		if (stoi(givenTime) > stoi(buildingClosingTime))
			return true;
		else return false;
	}
	else puts("Connection to DataBase has failed");
}