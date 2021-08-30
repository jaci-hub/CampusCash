#pragma once
#include <iostream>
#include <string>
#include "file_com_pragmaonce_mysql.h"
#include "feesManagement.h"
using namespace std;

int qorderTotal;

void order_total() {
    //Stablishing the connection to mysql database
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

    if (conn) {
        cout << "*Subtotal: $" << myOrder.foodOrderTotal << "\n";
        cout << "*Delivery Fee: $" << "\n";
        cout << "*** TOTAL: $" << "\n";

        //paymentMethod(); ???
    }
    else puts("Connection to DataBase has failed");
}