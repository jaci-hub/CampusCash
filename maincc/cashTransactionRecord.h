#pragma once
#include <iostream>
#include <string>
#include "file_com_pragmaonce_mysql.h"
#include "tableExists.h"
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
            //Create cashTransRecoTable if it doesnt exist yet
            if (tableExists("cashTransRecoTable") == false) {
                string queryCriarTable = "CREATE TABLE cashTransRecoTable(transactionCount INT KEY AUTO_INCREMENT, senderEmail VARCHAR(255) NOT NULL, receiverEmail VARCHAR(255) NOT NULL, amountSent DOUBLE(5, 2) NOT NULL, feeApplied DOUBLE(5, 2), transDateTime VARCHAR(255) NOT NULL)";
                const char* qCriarTable = queryCriarTable.c_str();
                qstateTransactionRec = mysql_query(conn, qCriarTable);
                if (qstateTransactionRec)
                    cout << "Query failed: " << mysql_error(conn) << "\n";

                cout << "No transactions!\n";
            }

            //Taking care of sender
            string queryEmail12amount = "SELECT senderEmail, amountSent, receiverEmail, transDateTime, transactionCount, feeApplied FROM cashTransRecoTable";
            const char* qEmail12amount = queryEmail12amount.c_str();
            qstateTransactionRec = mysql_query(conn, qEmail12amount);
            if (!qstateTransactionRec) {
                res = mysql_store_result(conn);
                while (row = mysql_fetch_row(res)) {
                    cout << "Transaction #" << row[4] << "\n";
                    cout << "Sender: " << row[0] << "\n";
                    cout << "Receiver: " << row[2] << "\n";
                    cout << "Amount: $" << row[1] << "\n";
                    cout << "Fee: $" << row[5] << "\n";
                    cout << "DateTime: " << row[3] << "\n * \n";
                }
            }
            else cout << "Query failed: " << mysql_error(conn) << "\n";
        }
        else puts("Connection to DataBase has failed");
}