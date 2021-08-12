#pragma once
#include<bits/stdc++.h>
#include "file_com_pragmaonce_mysql.h"

using namespace std;

int qstateTableExists;

bool tableExists(string tableName) {
	//Stablishing the connection to mysql database
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

	if (conn) {
		//CHECK IF TABLE EXISTS
		bool answer=false;
		string queryCheckTable = "SHOW TABLES LIKE '" + tableName + "'";
		const char* qCheckTable = queryCheckTable.c_str();
		qstateTableExists = mysql_query(conn, qCheckTable);
		if (!qstateTableExists) {
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
				answer = true;
		}
		else cout << "Query failed: " << mysql_error(conn) << "\n";

		return answer;
	}
	else puts("Connection to DataBase has failed");
}