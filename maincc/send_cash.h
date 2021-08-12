#pragma once
#include<bits/stdc++.h>
#include "criar_sender.h"
#include "criar_receiver.h"
#include "file_com_pragmaonce_mysql.h"
#include "getTransactionFee.h"
#include "getCurrentDateTime.h"
using namespace std;

int qstateTransaction;

//****send_cash function***
void send_cash() {
    //Stablishing the connection to mysql database
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

    if (conn) {
        cout << "*** Amount: ";
        cin >> amount_toSend; //from getTransactionFee.h
        //cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (amount_toSend <= 0) {
            cout << "Invalid!" << "\n";
            send_cash();
        }
        else if (amount_toSend > student1.get_balance()) {
            cout << "You do not have enough cash! " << "\n";
            send_cash();
        }
        else if (amount_toSend + get_transactionFee() > student1.get_balance()) {
            cout << "Couldn't pay the transaction fee! " << "\n";
            send_cash();
        }
        else if (amount_toSend <= student1.get_balance()) {
            //Taking care of sender
            string queryEmail1 = "SELECT studentBalance FROM studentdatatable WHERE studentEmail = '" + student1.get_email() + "'";
            const char* qEmail1 = queryEmail1.c_str();
            qstateTransaction = mysql_query(conn, qEmail1);
            if (!qstateTransaction) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                string oldCash = row[0];
                double newCash = stod(oldCash);
                newCash -= amount_toSend + get_transactionFee();

                //Update senders balance in the classSender
                student1.balance = newCash;

                //Update senders balance in the DB
                string newCashString = to_string(newCash);
                string querynewCash1 = "UPDATE studentdatatable SET studentBalance = '" + newCashString + "' WHERE studentEmail = '" + student1.get_email() + "'";
                const char* qnewCash1 = querynewCash1.c_str();
                qstateTransaction = mysql_query(conn, qnewCash1);
                if (qstateTransaction)
                    cout << "Query failed: " << mysql_error(conn) << "\n";
            }
            else cout << "Query failed: " << mysql_error(conn) << "\n";

            //Taking care of receiver
            string queryEmail2 = "SELECT studentBalance FROM studentdatatable WHERE studentEmail = '" + receiversEmail + "'";
            const char* qEmail2 = queryEmail2.c_str();
            qstateTransaction = mysql_query(conn, qEmail2);
            if (!qstateTransaction) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                string oldCash = row[0];
                double newCash = stod(oldCash);
                newCash += amount_toSend;

                //Update receivers balance in the DB
                string newCashString = to_string(newCash);
                string querynewCash2 = "UPDATE studentdatatable SET studentBalance = '" + newCashString + "' WHERE studentEmail = '" + receiversEmail + "'";
                const char* qnewCash2 = querynewCash2.c_str();
                qstateTransaction = mysql_query(conn, qnewCash2);
                if (qstateTransaction)
                    cout << "Query failed: " << mysql_error(conn) << "\n";
            }
            else cout << "Query failed: " << mysql_error(conn) << "\n";

            //Inserting values into cashTransRecoTable
            string amount_toSendString=to_string(amount_toSend), get_transactionFeeString=to_string(get_transactionFee());
            string queryEmail12amountSent = "INSERT INTO cashTransRecoTable (senderEmail, amountSent, receiverEmail, feeApplied, transDateTime) VALUES ('" + student1.get_email() + "', '" + amount_toSendString + "', '" + receiversEmail + "', '" + get_transactionFeeString + "', '" + getCurrentDateTime() + "')";
            const char* qEmail12amountSent = queryEmail12amountSent.c_str();
            qstateTransaction = mysql_query(conn, qEmail12amountSent);
            if (qstateTransaction) 
                cout << "Query failed: " << mysql_error(conn) << "\n";

            //Display transaction on the screen
            cout << "*** Campus Cash (CC)***" << "\n";
            cout << receiversName << " received $" << fixed << setprecision(2) << amount_toSend << "\n";
        }
    }
    else puts("Connection to DataBase has failed");
}
//*******