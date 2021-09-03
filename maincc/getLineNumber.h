#pragma once
#include <iostream>
#include <string>
#include "classOrderFood.h"
using namespace std;

int qstategetLineNumber;

int getLineNumber() {
    //Stablishing the connection to mysql database
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

    if (conn) {
        //get buildingOrderedFrom first
        string buildingOrderedFrom;
        string querySelectbuildingOrderedFrom = "SELECT buildingOrderedFrom FROM studentDataTable WHERE studentEmail = '" + student1.get_email() + "'";
        const char* qSelectbuildingOrderedFrom = querySelectbuildingOrderedFrom.c_str();
        qstategetLineNumber = mysql_query(conn, qSelectbuildingOrderedFrom);
        if (!qstategetLineNumber) {
            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);
            buildingOrderedFrom = row[0];

            if (buildingOrderedFrom == "none")
                cout << "1- Order food" << "\n";
        }
        else cout << "Query failed: " << mysql_error(conn) << "\n";

        buildingOrderedFrom = formatName(buildingOrderedFrom);

        string querySelectOrderID = "SELECT orderID FROM " + buildingOrderedFrom + "OrdersTable WHERE studentEmail = '" + student1.get_email() + "'";
        const char* qSelectOrderID = querySelectOrderID.c_str();
        qstategetLineNumber = mysql_query(conn, qSelectOrderID);
        if (!qstategetLineNumber) {
            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);
            return stoi(row[0]);
        }
        else cout << "Query failed: " << mysql_error(conn) << "\n";
    }
    else puts("Connection to DataBase has failed");
}