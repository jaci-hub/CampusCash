#pragma once
#include<bits/stdc++.h>
#include "file_com_pragmaonce_mysql.h"

using namespace std;

int qstateCurrentMonth;

string getCurrentMonth() {
	//Stablishing the connection to mysql database
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

	if (conn) {
		//Getting the current MONTH
		string queryCurrentDateTime = "SELECT EXTRACT(MONTH FROM NOW())";
		const char* qCurrentDateTime = queryCurrentDateTime.c_str();
		qstateCurrentMonth = mysql_query(conn, qCurrentDateTime);
		if (!qstateCurrentMonth) {
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			return row[0];
		}
		else cout << "Query failed: " << mysql_error(conn) << "\n";
	}
	else puts("Connection to DataBase has failed");
}