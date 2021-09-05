#pragma once
#include <iostream>
#include <string>
#include "feesManagement.h"
using namespace std;

int qstategetFee;

double getFee(string feeTableName, string foodBuildingNameFormated, string feeName) {
	//Stablishing the connection to mysql database
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

	if (conn) {
		if (foodBuildingNameFormated == "none") {
			string queryGettingTransactionFee = "SELECT percentageFee FROM " + feeTableName + " WHERE feeName = '" + feeName + "'";
			const char* qGettingTransactionFee = queryGettingTransactionFee.c_str();
			qstategetFee = mysql_query(conn, qGettingTransactionFee);
			if (!qstategetFee) {
				res = mysql_store_result(conn);
				row = mysql_fetch_row(res);
				return stod(row[0]);
			}
			else cout << "Query failed: " << mysql_error(conn) << "\n";
		}
		else {
			string queryGettingDeliveryFee = "SELECT " + foodBuildingNameFormated + " FROM " + feeTableName + " WHERE feeName = '" + feeName + "'";
			const char* qGettingDeliveryFee = queryGettingDeliveryFee.c_str();
			qstategetFee = mysql_query(conn, qGettingDeliveryFee);
			if (!qstategetFee) {
				res = mysql_store_result(conn);
				row = mysql_fetch_row(res);
				return stod(row[0]);
			}
			else cout << "Query failed: " << mysql_error(conn) << "\n";
		}
	}
	else puts("Connection to DataBase has failed");
}