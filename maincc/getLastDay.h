#pragma once
#include <iostream>
#include <string>
#include "file_com_pragmaonce_mysql.h"
#include "getCurrentDateTime.h"

using namespace std;

int qstateLastDay;

string getLastDay(string mes, string ano) {
	//Stablishing the connection to mysql database
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

	if (conn) {
		//Getting the last DATE
		string lastDate, queryCurrentDateTime = "SELECT LAST_DAY('" + ano + "-" + mes + "-" + getCurrentDay() + "')";
		const char* qCurrentDateTime = queryCurrentDateTime.c_str();
		qstateLastDay = mysql_query(conn, qCurrentDateTime);
		if (!qstateLastDay) {
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			lastDate = row[0];
		}
		else cout << "Query failed: " << mysql_error(conn) << "\n";

		//Getting the last DAY
		string queryCurrentDate = "SELECT EXTRACT(DAY FROM '" + lastDate + "')";
		const char* qCurrentDate = queryCurrentDate.c_str();
		qstateLastDay = mysql_query(conn, qCurrentDate);
		if (!qstateLastDay) {
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			return row[0];
		}
		else cout << "Query failed: " << mysql_error(conn) << "\n";
	}
	else puts("Connection to DataBase has failed");
}