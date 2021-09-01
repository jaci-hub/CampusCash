#pragma once
#include <iostream>
#include <string>
#include "classSender.h"
#include "formatName.h"

using namespace std;

int qstateCancelOrder;

//***cancelOrder function***
void cancelOrder() {
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