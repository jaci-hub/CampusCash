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
        //get the students email first
        string studentEmail;
        string querystudentEmail = "SELECT deliverTo FROM staffDataTable WHERE staffEmail = '" + staff.get_email() + "'";
        const char* qstudentEmail = querystudentEmail.c_str();
        qstateEntregador = mysql_query(conn, qstudentEmail);
        cout << "* To be delivered *\n";
        if (!qstateEntregador) {
            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);
            studentEmail = row[0];
        }
        else cout << "Query failed: " << mysql_error(conn) << "\n";

        if (studentEmail != "none") {
            //get the buildingOrderedFrom
            string buildingOrderedFrom;
            string querybuildingOrderedFrom = "SELECT buildingOrderedFrom FROM studentDataTable WHERE studentEmail = '" + studentEmail + "'";
            const char* qbuildingOrderedFrom = querybuildingOrderedFrom.c_str();
            qstateEntregador = mysql_query(conn, qbuildingOrderedFrom);
            if (!qstateEntregador) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                buildingOrderedFrom = row[0];
            }
            else cout << "Query failed: " << mysql_error(conn) << "\n";

            //go to the orders Table and get the students order info
            string queryFoodBuildingOrders = "SELECT * FROM " + buildingOrderedFrom + "OrdersTable WHERE studentEmail = '" + studentEmail + "'";
            const char* qFoodBuildingOrders = queryFoodBuildingOrders.c_str();
            qstateEntregador = mysql_query(conn, qFoodBuildingOrders);
            if (!qstateEntregador) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
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
                cout << "Payment Method: " << row[12] << "\n";
                cout << "DateTime: " << row[13] << "\n\n";
            }
            else cout << "Query failed: " << mysql_error(conn) << "\n";
        }
        else cout << "* Nothing\n\n";
    }
    else puts("Connection to DataBase has failed");
}