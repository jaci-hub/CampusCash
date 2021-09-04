#pragma once
#include <iostream>
#include <string>
#include "feesManagement.h"
using namespace std;

int qstateGetStaffSpecificInfo;

string getStaffSpecificInfo(string staffEmail, string columnToLookAt) {
	//Stablishing the connection to mysql database
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

	if (conn) {
		string queryGetStaffSpecificInfo = "SELECT " + columnToLookAt + " FROM staffDataTable WHERE staffEmail = '" + staffEmail + "'";
		const char* qGetStaffSpecificInfo = queryGetStaffSpecificInfo.c_str();
		qstateGetStaffSpecificInfo = mysql_query(conn, qGetStaffSpecificInfo);
		if (!qstateGetStaffSpecificInfo) {
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			return row[0];
		}
		else cout << "Query failed: " << mysql_error(conn) << "\n";
	}
	else puts("Connection to DataBase has failed");
}