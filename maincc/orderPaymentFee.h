#pragma once
#include <iostream>
#include <string>
#include "orderFood.h"
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
        
    }
    else puts("Connection to DataBase has failed");
}