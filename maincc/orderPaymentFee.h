#pragma once
#include <iostream>
#include <string>
#include "feesManagement.h"
#include "formatName.h"
using namespace std;

int qstateorderPaymentFee;

double orderPaymentFee() {
    //Stablishing the connection to mysql database
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

    if (conn) {
        string querySelectFee = "SELECT PercentageFee FROM feesTable WHERE feeName = '" + myOrder.get_selectedOnOffCampus() + " Delivery Fee'";
        const char* qSelectFee = querySelectFee.c_str();
        qstateorderPaymentFee = mysql_query(conn, qSelectFee);
        if (!qstateorderPaymentFee) {
            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);
            return stod(row[0])* myOrder.get_foodOrderTotal()/100.00;
        }
        else cout << "Query failed: " << mysql_error(conn) << "\n";
    }
    else puts("Connection to DataBase has failed");
}