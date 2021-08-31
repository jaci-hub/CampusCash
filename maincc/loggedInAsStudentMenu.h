#pragma once
#include <iostream>
#include <string>
#include "classSender.h"
#include "formatName.h"
using namespace std;

int qstateLoggedInAsStudentMenu;

//***Opcoes do menu***
unsigned int option;
void menu() {
    //Stablishing the connection to mysql database
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

    if (conn) {
        //get buildingOrderedFrom first
        string buildingOrderedFrom;
        string querySelectOrderID = "SELECT buildingOrderedFrom FROM studentDataTable WHERE studentEmail = '" + student1.get_email() + "'";
        const char* qSelectOrderID = querySelectOrderID.c_str();
        qstateLoggedInAsStudentMenu = mysql_query(conn, qSelectOrderID);
        if (!qstateLoggedInAsStudentMenu) {
            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);
            buildingOrderedFrom = row[0];
        }
        else cout << "Query failed: " << mysql_error(conn) << "\n";

        buildingOrderedFrom = formatName(buildingOrderedFrom);

        //select lineNumber from DB
        if (tableExists(buildingOrderedFrom + "OrdersTable") == true) {
            string querySelectOrderID = "SELECT orderID FROM " + buildingOrderedFrom + "OrdersTable WHERE studentEmail = '" + student1.get_email() + "'";
            const char* qSelectOrderID = querySelectOrderID.c_str();
            qstateLoggedInAsStudentMenu = mysql_query(conn, qSelectOrderID);
            if (!qstateLoggedInAsStudentMenu) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                if (stoi(row[0]) <= 0)
                    cout << "** Your food is on the Way! **\n"; //REMOVE THIS WHEN FOOD IS DELIVERED!!
                else if (stoi(row[0]) == 1)
                    cout << "** Your food is being prepared right now! **\n";
                if (stoi(row[0]) > 1) {
                    cout << "** Line#: " << stoi(row[0]) << "\n";
                    cout << "0- Cancel order" << "\n";
                }
            }
            else cout << "Query failed: " << mysql_error(conn) << "\n";
        }

        cout << "1- Order food" << "\n";
        cout << "2- Send cash" << "\n";
        cout << "3- Log out" << "\n";
        cout << "Please, enter an option: ";
        cin >> option;
        if (option < 0 || option > 3) {
            //system("clear");
            menu();
        }
    }
}
//*******