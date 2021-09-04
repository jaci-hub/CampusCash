#pragma once
#include <iostream>
#include <string>
#include "file_com_pragmaonce_mysql.h"
#include "formatName.h"
#include "getName_fromTable.h"
#include "listarCoisas.h"
#include "diningManagement.h"
#include "cancelAllOrders.h"
#include "cancelOrderOne.h"

using namespace std;

int qstateShowOrders;

void show_orders() {
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
                    allinOne_class.buildingName = getName_fromTable("foodBuildingsTable", "foodBuildingName", "foodBuildingID", foodBuildingChoice);

                    //take out all spaces and lower-case all letters
                    allinOne_class.buildingName = formatName(allinOne_class.buildingName);

                    //Getting the orders from that building
                    bool next = false;
                    if (tableExists(allinOne_class.get_buildingName() + "OrdersTable") == true) {
                        string queryFoodBuildingOrders = "SELECT * FROM " + allinOne_class.get_buildingName() + "OrdersTable";
                        const char* qFoodBuildingOrders = queryFoodBuildingOrders.c_str();
                        qstateShowOrders = mysql_query(conn, qFoodBuildingOrders);
                        cout << "* Orders *\n";
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
                                    cout << "DateTime: " << row[13] << "\n"; //row[12] is paymentMethod
                                    cout << "***\n";
                                }
                            }
                        }
                        else cout << "Query failed: " << mysql_error(conn) << "\n";
                    }
                    else cout << "No order!\n";

                    //getting the entregador email first
                    string entregadorEmail;
                    bool entregadorAvailable = false;
                    string querygetEmail = "SELECT staffEmail FROM staffDataTable WHERE staffType = 'Entregador' AND deliverTo = 'none'";
                    const char* qgetEmail = querygetEmail.c_str();
                    qstateShowOrders = mysql_query(conn, qgetEmail);
                    if (!qstateShowOrders) {
                        res = mysql_store_result(conn);
                        while (row = mysql_fetch_row(res)) {
                            entregadorEmail = row[0];
                            entregadorAvailable = true;
                        }
                    }
                    else cout << "Query failed: " << mysql_error(conn) << "\n";
                    
                    if (entregadorAvailable == true)
                        cout << "n- Next\n";
                    else cout << "* No deliveryman available!\n";
                    cout << "q- Cancel Order #1\n";
                    cout << "c- Cancel All Orders\n";
                    cout << "e- EXIT\n";
                    cout << "Please, enter an option: ";
                    string ordersOption;
                    cin >> ordersOption;

                    //Next in line
                    if (ordersOption == "n" && next == true) {
                        //UPDATE IN DB
                        string queryUpdateOrderID = "UPDATE " + allinOne_class.get_buildingName() + "OrdersTable SET orderID = orderID - 1";
                        const char* qUpdateOrderID = queryUpdateOrderID.c_str();
                        qstateShowOrders = mysql_query(conn, qUpdateOrderID);
                        if (qstateShowOrders)
                            cout << "Query failed: " << mysql_error(conn) << "\n";

                            //*** Assigning delivery***
                        //get the email of the student that just got order done (orderID = 0)
                        string StudentEmail;
                        string querygetorderStudentEmail = "SELECT studentEmail FROM " + allinOne_class.get_buildingName() + "OrdersTable WHERE orderID = 0";
                        const char* qgetorderStudentEmail = querygetorderStudentEmail.c_str();
                        qstateShowOrders = mysql_query(conn, qgetorderStudentEmail);
                        if (!qstateShowOrders) {
                            res = mysql_store_result(conn);
                            row = mysql_fetch_row(res);
                            StudentEmail = row[0];
                        }
                        else cout << "Query failed: " << mysql_error(conn) << "\n";

                        //***set entregador whose deliverTo is 'none' to StudentEmail
                        string queryUpdatedeliverTo = "UPDATE staffDataTable SET deliverTo = '" + StudentEmail + "' WHERE staffEmail = '" + entregadorEmail + "'";
                        const char* qUpdatedeliverTo = queryUpdatedeliverTo.c_str();
                        qstateShowOrders = mysql_query(conn, qUpdatedeliverTo);
                        if (qstateShowOrders)
                            cout << "Query failed: " << mysql_error(conn) << "\n";                        

                        //set the entregadorEmail in student DB as the email of the entregador
                        string queryUpdateentregadorEmail = "UPDATE studentDataTable SET entregadorEmail = '" + entregadorEmail + "' WHERE studentEmail = '" + StudentEmail + "'";
                        const char* qUpdateentregadorEmail = queryUpdateentregadorEmail.c_str();
                        qstateShowOrders = mysql_query(conn, qUpdateentregadorEmail);
                        if (qstateShowOrders)
                            cout << "Query failed: " << mysql_error(conn) << "\n";

                        goto showOrders;
                    }

                    else if (ordersOption == "n" && next == false) {
                        cout << "No order!\n";
                        goto showOrders;
                    }

                    //Cancel order #1 and refund student
                    else if (ordersOption == "q" && next == true) {
                        cout << "** Are you sure? THIS CANNOT BE UNDONE!\n";
                        cout << "1- YES\n";
                        cout << "2- Back\n";
                        cout << "Please, enter an option: ";
                        int cancelamento;
                        cin >> cancelamento;
                        if (cancelamento == 1) {
                            cancelOrderOne();

                            goto showOrders;
                        }
                        if (cancelamento == 2)
                            goto showOrders;
                    }

                    else if (ordersOption == "q" && next == false) {
                        cout << "No order!\n";
                        goto showOrders;
                    }

                    //Cancel all orders and refund students
                    else if (ordersOption == "c" && next == true) {
                        cout << "** Are you sure? THIS CANNOT BE UNDONE!\n";
                        cout << "1- YES\n";
                        cout << "2- Back\n";
                        cout << "Please, enter an option: ";
                        int cancelamento;
                        cin >> cancelamento;
                        if (cancelamento == 1) {
                            cancelAllOrders();

                            goto showOrders;
                        }
                        if (cancelamento == 2)
                            goto showOrders;
                    }

                    else if (ordersOption == "c" && next == false) {
                        cout << "No order!\n";
                        goto showOrders;
                    }

                    if (ordersOption == "e")
                        goto show_ordersEnd;
                }
                else if(foodBuildingChoice == "e")
                    goto show_ordersEnd;
            }
        }
    }
    else puts("Connection to DataBase has failed");

    //end funcao
show_ordersEnd:
    cout << "";
}