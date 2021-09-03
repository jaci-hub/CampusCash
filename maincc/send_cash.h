#pragma once
#include <iostream>
#include <string>
#include "criar_sender.h"
#include "criar_receiver.h"
#include "file_com_pragmaonce_mysql.h"
#include "getFee.h"
#include "getCurrentDateTime.h"
#include "tableExists.h"
using namespace std;

int qstateCashTransaction;

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
        double amount_toSend;
        cin >> amount_toSend;
        if (amount_toSend <= 0) {
            cout << "Invalid!" << "\n";
            send_cash();
        }
        else if (amount_toSend > student1.get_balance()) {
            cout << "You do not have enough cash! " << "\n";
            send_cash();
        }
        else if (amount_toSend * (1.00 + getFee("Cash Transaction Fee") / 100.00) > student1.get_balance()) {
            cout << "Couldn't pay the transaction fee! " << "\n";
            send_cash();
        }
        else if (amount_toSend <= student1.get_balance()) {
            //show total
            cout << "Amount: $" << amount_toSend << "\n";
            cout << "Transaction fee: $" << amount_toSend * getFee("Cash Transaction Fee") / 100.00 << "\n";
            cout << "TOTAL: $" << amount_toSend * (1.00 + getFee("Cash Transaction Fee") / 100.00) << "\n";
            cout << "* Select an option\n";
            cout << "1- Make transaction\n";
            cout << "2- Cancel transaction\n";
            cout << "Please, enter an option: ";
            int transactionConfirmation;
            cin >> transactionConfirmation;
            if (transactionConfirmation == 1) {
                //Taking care of sender
                string queryEmail1 = "SELECT studentBalance FROM studentdatatable WHERE studentEmail = '" + student1.get_email() + "'";
                const char* qEmail1 = queryEmail1.c_str();
                qstateCashTransaction = mysql_query(conn, qEmail1);
                if (!qstateCashTransaction) {
                    res = mysql_store_result(conn);
                    row = mysql_fetch_row(res);
                    string oldCash = row[0];
                    double newCash = stod(oldCash);
                    newCash -= amount_toSend * (1.00 + getFee("Cash Transaction Fee") / 100.00);

                    //Update senders balance in the classSender
                    student1.balance = newCash;

                    //Update senders balance in the DB
                    string newCashString = to_string(newCash);
                    string querynewCash1 = "UPDATE studentdatatable SET studentBalance = '" + newCashString + "' WHERE studentEmail = '" + student1.get_email() + "'";
                    const char* qnewCash1 = querynewCash1.c_str();
                    qstateCashTransaction = mysql_query(conn, qnewCash1);
                    if (qstateCashTransaction)
                        cout << "Query failed: " << mysql_error(conn) << "\n";
                }
                else cout << "Query failed: " << mysql_error(conn) << "\n";

                //Taking care of receiver
                string queryEmail2 = "SELECT studentBalance FROM studentdatatable WHERE studentEmail = '" + receiversEmail + "'";
                const char* qEmail2 = queryEmail2.c_str();
                qstateCashTransaction = mysql_query(conn, qEmail2);
                if (!qstateCashTransaction) {
                    res = mysql_store_result(conn);
                    row = mysql_fetch_row(res);
                    string oldCash = row[0];
                    double newCash = stod(oldCash);
                    newCash += amount_toSend;

                    //Update receivers balance in the DB
                    string newCashString = to_string(newCash);
                    string querynewCash2 = "UPDATE studentdatatable SET studentBalance = '" + newCashString + "' WHERE studentEmail = '" + receiversEmail + "'";
                    const char* qnewCash2 = querynewCash2.c_str();
                    qstateCashTransaction = mysql_query(conn, qnewCash2);
                    if (qstateCashTransaction)
                        cout << "Query failed: " << mysql_error(conn) << "\n";
                }
                else cout << "Query failed: " << mysql_error(conn) << "\n";

                //Display transaction on the screen
                cout << "*** Campus Cash (CC)***" << "\n";
                cout << receiversName << " received $" << fixed << setprecision(2) << amount_toSend << "\n";
            }
            if (transactionConfirmation == 2)
                goto send_cashEnd;
        }
    }
    else puts("Connection to DataBase has failed");

send_cashEnd:
    cout << "";
}
//*******