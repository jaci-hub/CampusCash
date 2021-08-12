#pragma once
#include<bits/stdc++.h>
#include "file_com_pragmaonce_mysql.h"
#include "classQueue.h"
#include "formatName.h"
#include "getName_fromTable.h"
#include "listarCoisas.h"
using namespace std;

int qstateShowOrders, ordersOption;

void show_orders_byFoodBuilding() {
    //Stablishing the connection to mysql database
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

    if (conn) {
        cout << "* Select building \n";
        //listing the buildings in the foodBuildingsTable
        listarCoisas("foodBuildingID", "foodBuildingName", "foodBuildingsTable");

        int foodBuildingChoice;
        cout << "Please, enter an option: ";
        cin >> foodBuildingChoice;

        string buildingName, foodBuildingChoiceString = to_string(foodBuildingChoice);

        //Getting the food buildings name
        buildingName = getName_fromTable("foodBuildingsTable", "foodBuildingName", "foodBuildingID", foodBuildingChoiceString);

        //take out all spaces and lower-case all letters
        buildingName = formatName(buildingName);

        //************ASK FOR PIN HERE TO GET TO SEE THE BUILDINGS ORDERS????????

        //Getting the orders from that building //IMPLEMENT QUEUE HERE!!!
        string queryFoodBuildingOrders = "SELECT * FROM " + buildingName + "OrdersTable";
        const char* qFoodBuildingOrders = queryFoodBuildingOrders.c_str();
        qstateShowOrders = mysql_query(conn, qFoodBuildingOrders);
        cout << "* Orders *\n\n";
        if (!qstateShowOrders) {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res)) {
                cout << "Email: " << row[0] << "\n";
                cout << "Meal type: " << row[1] << "\n";
                cout << "Food: " << row[2] << "\n";
                cout << "Drink: " << row[3] << "\n";
                cout << "Sides: " << row[4] << "\n";
                cout << "Other: " << row[5] << "\n";
                cout << "House-Room: " << row[8] << "\n\n";
            }
        }
        else cout << "Query failed: " << mysql_error(conn) << "\n";

        cout << "1- Next\n";
        cout << "2- Cancel Orders\n";
        cout << "3- Back to Menu\n";
        cout << "Please, enter an option: ";
        cin >> ordersOption;

        //Next in line
        if (ordersOption == 1) {
            //enqueue the next in line and dequeue the first in line after "your food is on the way!" message has been sent
        }

        //Cancel all orders and refund students
        else if (ordersOption == 2) {
            //clear queue and refund
        }
    }
    else puts("Connection to DataBase has failed");
}