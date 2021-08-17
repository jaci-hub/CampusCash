#pragma once
#include <iostream>
#include <string>
#include "criar_orderFood.h"
#include "delivery.h"
#include "feesManagement.h"
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
        if (on_off == 1) {
            string queryGettingOnCampusDeliveryFee = "SELECT percentageFee FROM feesTable WHERE feeName = 'OnCampusDeliveryFee'";
            const char* qGettingOnCampusDeliveryFee = queryGettingOnCampusDeliveryFee.c_str();
            qstateorderPaymentFee = mysql_query(conn, qGettingOnCampusDeliveryFee);
            if (!qstateorderPaymentFee) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                return order1.get_foodOrderTotal() * stod(row[0]) / 100.00;
            }
            else cout << "Query failed: " << mysql_error(conn) << "\n";
        }

        else if (on_off == 2) {
            string queryGettingOffCampusDeliveryFee = "SELECT percentageFee FROM feesTable WHERE feeName = 'OffCampusDeliveryFee'";
            const char* qGettingOffCampusDeliveryFee = queryGettingOffCampusDeliveryFee.c_str();
            qstateorderPaymentFee = mysql_query(conn, qGettingOffCampusDeliveryFee);
            if (!qstateorderPaymentFee) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                return order1.get_foodOrderTotal() * stod(row[0]) / 100.00;
            }
            else cout << "Query failed: " << mysql_error(conn) << "\n";
        }
    }
    else puts("Connection to DataBase has failed");
}