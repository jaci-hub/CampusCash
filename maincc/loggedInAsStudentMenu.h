#pragma once
#include <iostream>
#include <string>
#include "classSender.h"
#include "formatName.h"
#include "allinOne_class.h"
#include "getLineNumber.h"
using namespace std;

int qstateLoggedInAsStudentMenu;

//***Opcoes do menu***
string option;
void menu() {
    //Stablishing the connection to mysql database
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

    if (conn) {
        //get canceledOrderMessage
        string zeroOne;
        string querySelectcanceledOrderMessage = "SELECT canceledOrderMessage FROM studentDataTable WHERE studentEmail = '" + student1.get_email() + "'";
        const char* qSelectcanceledOrderMessage = querySelectcanceledOrderMessage.c_str();
        qstateLoggedInAsStudentMenu = mysql_query(conn, qSelectcanceledOrderMessage);
        if (!qstateLoggedInAsStudentMenu) {
            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);
            zeroOne = row[0];
            if (zeroOne == "1") {
                //Display message 'SORRY, YOUR ORDER HAS BEEN CANCELED!'
                cout << "** SORRY, YOUR ORDER HAS BEEN CANCELED!\n";
                cout << "o- Ok" << "\n";
            }
        }
        else cout << "Query failed: " << mysql_error(conn) << "\n";

        //get buildingOrderedFrom first
        string buildingOrderedFrom;
        string querySelectOrderID = "SELECT buildingOrderedFrom FROM studentDataTable WHERE studentEmail = '" + student1.get_email() + "'";
        const char* qSelectOrderID = querySelectOrderID.c_str();
        qstateLoggedInAsStudentMenu = mysql_query(conn, qSelectOrderID);
        if (!qstateLoggedInAsStudentMenu) {
            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);
            buildingOrderedFrom = row[0];

            if(buildingOrderedFrom == "none")
                cout << "1- Order food" << "\n";
        }
        else cout << "Query failed: " << mysql_error(conn) << "\n";

        buildingOrderedFrom = formatName(buildingOrderedFrom);

        bool thereIsOrder = false;
        if (tableExists(buildingOrderedFrom + "OrdersTable") == true) {
            string queryCheckIfThereIsOrder = "SELECT orderID FROM " + buildingOrderedFrom + "OrdersTable WHERE studentEmail = '" + student1.get_email() + "'";
            const char* qCheckIfThereIsOrder = queryCheckIfThereIsOrder.c_str();
            qstateLoggedInAsStudentMenu = mysql_query(conn, qCheckIfThereIsOrder);
            if (!qstateLoggedInAsStudentMenu) {
                res = mysql_store_result(conn);
                while (row = mysql_fetch_row(res))
                    thereIsOrder = true;
            }
            else cout << "Query failed: " << mysql_error(conn) << "\n";
        }

        //check lineNumber from DB
        if (tableExists(buildingOrderedFrom + "OrdersTable") == true && thereIsOrder == true) {
            if (getLineNumber() <= 0) {
                cout << "** Your order is on the way! **\n";
                cout << "r- Received" << "\n";
            }
            else if (getLineNumber() == 1)
                cout << "** Your order is being prepared right now! **\n";
            else if (getLineNumber() > 1) {
                cout << "** Line#: " << getLineNumber() << "\n";
                cout << "c- Cancel order" << "\n";
            }
        }

        cout << "m- Send meal" << "\n";
        cout << "2- Send cash" << "\n";
        cout << "3- Log out" << "\n";
        cout << "Please, enter an option: ";
        cin >> option;
    }
    else puts("Connection to DataBase has failed");
}
//*******