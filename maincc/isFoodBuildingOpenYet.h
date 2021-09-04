#pragma once
#include <iostream>
#include <string>
#include "file_com_pragmaonce_mysql.h"

using namespace std;

int qstateisFoodBuildingOpenYet;

bool isFoodBuildingOpenYet(string foodBuildingNameFormated, string AnOpeningTime) {
	//Stablishing the connection to mysql database
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

	if (conn) {
		return true;
	}
	else puts("Connection to DataBase has failed");
}