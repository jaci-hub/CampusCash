#pragma once
#include <iostream>
#include <string>
#include "classSender.h"
#include "formatName.h"

using namespace std;

int qstateReceivedOrder;

//***receivedOrder function***
void receivedOrder() {
    //Stablishing the connection to mysql database
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

    if (conn) {
        //remove student from orderstable
        //get buildingOrderedFrom first
        string buildingOrderedFrom;
        string querySelectOrderID = "SELECT buildingOrderedFrom FROM studentDataTable WHERE studentEmail = '" + student1.get_email() + "'";
        const char* qSelectOrderID = querySelectOrderID.c_str();
        qstateReceivedOrder = mysql_query(conn, qSelectOrderID);
        if (!qstateReceivedOrder) {
            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);
            buildingOrderedFrom = row[0];
        }
        else cout << "Query failed: " << mysql_error(conn) << "\n";

        buildingOrderedFrom = formatName(buildingOrderedFrom);

        string queryRem = "DELETE FROM " + buildingOrderedFrom + "OrdersTable WHERE studentEmail = '" + student1.get_email() + "'";
        const char* qRem = queryRem.c_str();
        qstateReceivedOrder = mysql_query(conn, qRem);
        if (qstateReceivedOrder)
            cout << "Query failed: " << mysql_error(conn) << "\n";

        //setting buildingOrderedFrom to 'none'
        string queryUpdatebuildingOrderedFrom = "UPDATE studentdatatable SET buildingOrderedFrom = 'none' WHERE studentEmail = '" + student1.get_email() + "'";
        const char* qUpdatebuildingOrderedFrom = queryUpdatebuildingOrderedFrom.c_str();
        qstateReceivedOrder = mysql_query(conn, qUpdatebuildingOrderedFrom);
        if (qstateReceivedOrder)
            cout << "Query failed: " << mysql_error(conn) << "\n";
    }
    else puts("Connection to DataBase has failed");
}