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
        //getting the meal price
        string queryGettingMealPrice = "SELECT price FROM " + myOrder.get_selectedBuilding() + "MealsTimeAndPrice WHERE meal = '" + myOrder.get_selectedMeal() + "'";
        const char* qGettingMealPrice = queryGettingMealPrice.c_str();
        qorderTotal = mysql_query(conn, qGettingMealPrice);
        if (!qorderTotal) {
            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);
            myOrder.foodOrderTotal = stod(row[0]);
        }
        else cout << "Query failed: " << mysql_error(conn) << "\n";

        //adding the price of the sides
        myOrder.foodOrderTotal += myOrder.get_selectedSideOnePrice() + myOrder.get_selectedSideTwoPrice() + myOrder.get_selectedSideThreePrice();

        cout << "*Subtotal: $" << myOrder.foodOrderTotal << "\n";
        cout << "*Delivery Fee: $" << "\n";
        cout << "*** TOTAL: $" << "\n";

        //paymentMethod(); ???
    }
    else puts("Connection to DataBase has failed");
}