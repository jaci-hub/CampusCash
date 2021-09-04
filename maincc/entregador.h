#pragma once
#include <iostream>
#include <string>
#include "classStaff.h"
#include "file_com_pragmaonce_mysql.h"
using namespace std;

int qstateEntregador;

//***entregador function***
void entregador() {
    //Stablishing the connection to mysql database
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

    if (conn) {
        cout << "No delivery!\n";
    }
    else puts("Connection to DataBase has failed");
}