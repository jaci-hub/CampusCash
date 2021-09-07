#pragma once
#include <iostream>
#include <string>
#include "classOrderFood.h"
using namespace std;

int qstatesetLineNumber;

int setLineNumber() {
	//Stablishing the connection to mysql database
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

	if (conn) {
        int countRows, lastOrder, lineNumber;
        //get the countRows
        string querySelectcountRows = "SELECT COUNT(*) FROM " + formatName(myOrder.get_selectedBuilding()) + "OrdersTable";
        const char* qSelectcountRows = querySelectcountRows.c_str();
        qstatesetLineNumber = mysql_query(conn, qSelectcountRows);
        if (!qstatesetLineNumber) {
            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);
            countRows = stoi(row[0]);
        }
        else cout << "Query failed: " << mysql_error(conn) << "\n";

        //show the student line number IF the order is placed
        if (countRows == 0)
            lineNumber = 1;
        else {
            string querySelectOrderID = "SELECT MAX(orderID) FROM " + formatName(myOrder.get_selectedBuilding()) + "OrdersTable";
            const char* qSelectOrderID = querySelectOrderID.c_str();
            qstatesetLineNumber = mysql_query(conn, qSelectOrderID);
            if (!qstatesetLineNumber) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                lastOrder = stoi(row[0]);
                if (lastOrder <= 0)
                    lineNumber = 1;
                else lineNumber = lastOrder + 1;
            }
            else cout << "Query failed: " << mysql_error(conn) << "\n";
        }

        return lineNumber;
	}
	else puts("Connection to DataBase has failed");
}