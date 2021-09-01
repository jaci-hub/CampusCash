#pragma once
#include <iostream>
#include <string>
#include "file_com_pragmaonce_mysql.h"
#include "formatName.h"
#include "getName_fromTable.h"
#include "listarCoisas.h"
#include "diningManagement.h"
//#include "classOrderFood.h"
using namespace std;

int qstateShowOrders;

void show_orders_byFoodBuilding() {
    //Stablishing the connection to mysql database
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

    if (conn) {
        bool buildingsYet = false;

        //Create foodBuildingsTable if it doesnt exist yet
        if (tableExists("foodBuildingsTable") == false) {
            string queryCriarTable = "CREATE TABLE foodBuildingsTable(foodBuildingName VARCHAR(255) NOT NULL, foodBuildingID INT KEY AUTO_INCREMENT)";
            const char* qCriarTable = queryCriarTable.c_str();
            qstateShowOrders = mysql_query(conn, qCriarTable);
            if (qstateShowOrders)
                cout << "Query failed: " << mysql_error(conn) << "\n";

            cout << "** No building!\n";
        }

        else if (tableExists("foodBuildingsTable") == true) {
            string queryGettingName = "SELECT foodBuildingName FROM foodBuildingsTable";
            const char* qGettingName = queryGettingName.c_str();
            qstateShowOrders = mysql_query(conn, qGettingName);
            if (!qstateShowOrders) {
                res = mysql_store_result(conn);
                while (row = mysql_fetch_row(res))
                    buildingsYet = true;
            }
            else cout << "Query failed: " << mysql_error(conn) << "\n";

            if (buildingsYet == false) {
                cout << "** No building!!\n";
            }

            else if (buildingsYet == true) {
                cout << "* Select building \n";
                //listing the buildings in the foodBuildingsTable
                listarCoisas("foodBuildingID", "foodBuildingName", "foodBuildingsTable");
                cout << "e- EXIT\n";
                string foodBuildingChoice;
                cout << "Please, enter an option: ";
                cin >> foodBuildingChoice;
                if (isdigit(foodBuildingChoice[0]) != 0) {
                    showOrders:
                    //Getting the food buildings name
                    string buildingName = getName_fromTable("foodBuildingsTable", "foodBuildingName", "foodBuildingID", foodBuildingChoice);

                    //take out all spaces and lower-case all letters
                    buildingName = formatName(buildingName);

                    //************ASK FOR PIN HERE TO GET TO SEE THE BUILDINGS ORDERS????????

                    //Getting the orders from that building //IMPLEMENT QUEUE HERE!!!
                    string queryFoodBuildingOrders = "SELECT * FROM " + buildingName + "OrdersTable";
                    const char* qFoodBuildingOrders = queryFoodBuildingOrders.c_str();
                    qstateShowOrders = mysql_query(conn, qFoodBuildingOrders);
                    cout << "* Orders *\n";
                    bool next = false;
                    if (!qstateShowOrders) {
                        res = mysql_store_result(conn);
                        while (row = mysql_fetch_row(res)) {
                            if (stoi(row[0]) > 0) {
                                next = true;
                                cout << "Order #" << row[0] << "\n";
                                cout << "Email: " << row[1] << "\n";
                                cout << "Diet: " << row[2] << "\n";
                                cout << "Meal: " << row[3] << "\n";
                                cout << "Side One: " << row[4] << "\n";
                                cout << "Side Two: " << row[5] << "\n";
                                cout << "Side Three: " << row[6] << "\n";
                                cout << "ON/OFF campus: " << row[7] << "\n";
                                cout << "Dorm: " << row[8] << "\n";
                                cout << "Room: " << row[9] << "\n";
                                cout << "Subtotal: $" << row[10] << "\n";
                                cout << "Delivery Fee: $" << row[11] << "\n";
                                cout << "DateTime: " << row[13] << "\n";
                                cout << "***\n";
                            }
                        }
                    }
                    else cout << "Query failed: " << mysql_error(conn) << "\n";
                    
                    cout << "n- Next\n";
                    cout << "c- Cancel Orders\n";
                    cout << "e- EXIT\n";
                    cout << "Please, enter an option: ";
                    string ordersOption;
                    cin >> ordersOption;

                    //Next in line
                    if (ordersOption == "n" && next == true) {
                        //UPDATE IN DB
                        string queryUpdateOrderID = "UPDATE " + buildingName + "OrdersTable SET orderID = orderID - 1";
                        const char* qUpdateOrderID = queryUpdateOrderID.c_str();
                        qstateShowOrders = mysql_query(conn, qUpdateOrderID);
                        if (qstateShowOrders)
                            cout << "Query failed: " << mysql_error(conn) << "\n";

                        goto showOrders;
                    }

                    else if (ordersOption == "n" && next == false) {
                        cout << "No line!\n";
                        goto showOrders;
                    }

                    //Cancel all orders and refund students
                    else if (ordersOption == "c") {
                        //set everyones orderID less than the most negative number & set buildingorderedfrom = 'none' & refund students -- ask "ARE YOU SURE? THIS CANNOT BE UNDONE!"

                        goto showOrders;
                    }

                    if (ordersOption == "e")
                        goto show_orders_byFoodBuildingEnd;
                }
                else if(foodBuildingChoice == "e")
                    goto show_orders_byFoodBuildingEnd;
            }
        }
    }
    else puts("Connection to DataBase has failed");

    //end funcao
show_orders_byFoodBuildingEnd:
    cout << "";
}