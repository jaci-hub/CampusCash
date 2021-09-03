#pragma once
#include <iostream>
#include <string>
#include "feesManagement.h"
using namespace std;

int qstateget_transactionFee;

double getFee(string feeName) {
	//Stablishing the connection to mysql database
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

	if (conn) {
		string queryGettingTransactionFee = "SELECT percentageFee FROM feesTable WHERE feeName = '" + feeName + "'";
		const char* qGettingTransactionFee = queryGettingTransactionFee.c_str();
		qstateget_transactionFee = mysql_query(conn, qGettingTransactionFee);
		if (!qstateget_transactionFee) {
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			return stod(row[0]);
		}
		else cout << "Query failed: " << mysql_error(conn) << "\n";
	}
	else puts("Connection to DataBase has failed");
}