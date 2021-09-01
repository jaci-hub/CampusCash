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
        int maxOrderID;
        string studentEmail, buildingorderedfrom, paymentMethod;
        //get the max orderID (to set the for-loop)
                
        
        for(int i = maxOrderID; i > 0; i--) {
            //get studentEmail, buildingorderedfrom and paymentMethod
            


            //set buildingorderedfrom = 'none'
        

        
            //refund
        }

        //remove ALL orderID > 0 
    }
    else puts("Connection to DataBase has failed");
}