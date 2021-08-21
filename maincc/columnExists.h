#pragma once
#include <iostream>
#include <string>
#include "file_com_pragmaonce_mysql.h"

using namespace std;

int qstateColumnExists;

bool columnExists(string columnName, string tableName) {
	//Stablishing the connection to mysql database
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

	if (conn) {
		//CHECK IF COLUMN EXISTS
		bool answer = false;
		string queryCheckColumn = "SHOW COLUMNS FROM " + tableName;
		const char* qCheckColumn = queryCheckColumn.c_str();
		qstateColumnExists = mysql_query(conn, qCheckColumn);
		if (!qstateColumnExists) {
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res)) {
				if (columnName == row[0]) {
					answer = true;
					break;
				}
			}
		}
		else cout << "Query failed: " << mysql_error(conn) << "\n";

		return answer;
	}
	else puts("Connection to DataBase has failed");
}