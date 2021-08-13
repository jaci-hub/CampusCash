#pragma once
#include <iostream>
#include <string>
#include "file_com_pragmaonce_mysql.h"
using namespace std;

int qstateTransactionRec;

void cashTransactionRecord() {
    //Stablishing the connection to mysql database
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

    //the variables to be displayed
    string senderEmail, receiverEmail, amountSent, transDateTime;

        if (conn) {
            //Taking care of sender
            string queryEmail12amount = "SELECT senderEmail, amountSent, receiverEmail, transDateTime FROM cashTransRecoTable";
            const char* qEmail12amount = queryEmail12amount.c_str();
            qstateTransactionRec = mysql_query(conn, qEmail12amount);
            if (!qstateTransactionRec) {
                res = mysql_store_result(conn);
                while (row = mysql_fetch_row(res)) {
                    cout << row[0] <<" sent $" <<row[1]<<" to "<< row[2] <<"." <<" ("<< row[3] <<")" << "\n";
                }
            }
            else cout << "Query failed: " << mysql_error(conn) << "\n";
        }
        else puts("Connection to DataBase has failed");
}