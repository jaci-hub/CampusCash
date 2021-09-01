#pragma once
#include <iostream>
#include <string>
#include "classSender.h"
#include "classOrderFood.h"
#include "formatName.h"

using namespace std;

int qstateCancelAllOrders;

//***cancelAllOrders function***
void cancelAllOrders() {
    //Stablishing the connection to mysql database
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

    if (conn) {
        //remove everyone whose orderID > 0 
        
        //set buildingorderedfrom = 'none' 
        
        //refund students 
    }
    else puts("Connection to DataBase has failed");
}