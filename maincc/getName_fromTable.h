#pragma once
#include <iostream>
#include <string>
#include "file_com_pragmaonce_mysql.h"

using namespace std;

int qstateGetName;

string getName_fromTable(string tableName, string columnToLookAt, string IDcolumnName, string IDhere) {
	//Stablishing the connection to mysql database
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

	if (conn) {
		string queryGettingName = "SELECT " + columnToLookAt + " FROM " + tableName + " WHERE " + IDcolumnName + " = '" + IDhere + "'";
		const char* qGettingName = queryGettingName.c_str();
		qstateGetName = mysql_query(conn, qGettingName);
		if (!qstateGetName) {
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			return row[0];
		}
		else cout << "Query failed: " << mysql_error(conn) << "\n";
	}
	else puts("Connection to DataBase has failed");
}