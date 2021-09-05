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

int qstateMealTransaction;

//****send_meal function***
void send_meal() {
    //Stablishing the connection to mysql database
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

    if (conn) {
        if (student1.get_mealPlanBalance() <= 0) {
            cout << "You do not have enough meals!" << "\n";
            goto send_mealEnd;
        }
        else if (student1.get_balance() <= 0) {
            cout << "You do not have enough cash!" << "\n";
            goto send_mealEnd;
        }
        else if (student1.get_balance() * (getFee("feesTable", "none", "Meal Transaction Fee") / 100.00) > student1.get_balance()) {
            cout << "Couldn't pay the transaction fee! " << "\n";
            goto send_mealEnd;
        }
        else if (student1.get_balance() * (getFee("feesTable", "none", "Meal Transaction Fee") / 100.00) <= student1.get_balance()) {
            //show total
            cout << "Meal Transaction fee: $" << student1.get_balance() * getFee("feesTable", "none", "Meal Transaction Fee") / 100.00 << "\n";
            cout << "* Select an option\n";
            cout << "1- Make transaction\n";
            cout << "2- Cancel transaction\n";
            cout << "Please, enter an option: ";
            int transactionConfirmation;
            cin >> transactionConfirmation;
            if (transactionConfirmation == 1) {
                //Taking care of sender
                string queryEmail1 = "SELECT studentMeals, studentBalance FROM studentdatatable WHERE studentEmail = '" + student1.get_email() + "'";
                const char* qEmail1 = queryEmail1.c_str();
                qstateMealTransaction = mysql_query(conn, qEmail1);
                if (!qstateMealTransaction) {
                    res = mysql_store_result(conn);
                    row = mysql_fetch_row(res);
                    //meal
                    string oldMeal = row[0];
                    int newMeal = stoi(oldMeal);
                    newMeal -= 1;
                    //balance
                    string oldBalance = row[1];
                    double newBalance = stod(oldBalance);
                    newBalance -= student1.get_balance() * getFee("feesTable", "none", "Meal Transaction Fee") / 100.00;

                    //Update senders mealPlanBalance in the classSender
                    student1.mealPlanBalance = newMeal;
                    //Update senders balance in the classSender
                    student1.balance = newBalance;

                    //Update senders meal in the DB
                    string newMealString = to_string(newMeal);
                    string querynewMeal1 = "UPDATE studentdatatable SET studentMeals = '" + newMealString + "' WHERE studentEmail = '" + student1.get_email() + "'";
                    const char* qnewMeal1 = querynewMeal1.c_str();
                    qstateMealTransaction = mysql_query(conn, qnewMeal1);
                    if (qstateMealTransaction)
                        cout << "Query failed: " << mysql_error(conn) << "\n";

                    //Update senders balance in the DB
                    string newBalanceString = to_string(newBalance);
                    string querynewBalance1 = "UPDATE studentdatatable SET studentBalance = '" + newBalanceString + "' WHERE studentEmail = '" + student1.get_email() + "'";
                    const char* qnewBalance1 = querynewBalance1.c_str();
                    qstateMealTransaction = mysql_query(conn, qnewBalance1);
                    if (qstateMealTransaction)
                        cout << "Query failed: " << mysql_error(conn) << "\n";
                }
                else cout << "Query failed: " << mysql_error(conn) << "\n";

                //Taking care of receiver
                string queryEmail2 = "SELECT studentMeals FROM studentdatatable WHERE studentEmail = '" + receiversEmail + "'";
                const char* qEmail2 = queryEmail2.c_str();
                qstateMealTransaction = mysql_query(conn, qEmail2);
                if (!qstateMealTransaction) {
                    res = mysql_store_result(conn);
                    row = mysql_fetch_row(res);
                    string oldMeal = row[0];
                    double newMeal = stod(oldMeal);
                    newMeal += 1;

                    //Update receivers meal in the DB
                    string newMealString = to_string(newMeal);
                    string querynewMeal2 = "UPDATE studentdatatable SET studentMeals = '" + newMealString + "' WHERE studentEmail = '" + receiversEmail + "'";
                    const char* qnewMeal2 = querynewMeal2.c_str();
                    qstateMealTransaction = mysql_query(conn, qnewMeal2);
                    if (qstateMealTransaction)
                        cout << "Query failed: " << mysql_error(conn) << "\n";
                }
                else cout << "Query failed: " << mysql_error(conn) << "\n";

                //Display transaction on the screen
                cout << "*** Campus Cash (CC)***" << "\n";
                cout << receiversName << " received a meal\n";
            }
            if (transactionConfirmation == 2)
                goto send_mealEnd;
        }
    }
    else puts("Connection to DataBase has failed");

send_mealEnd:
    cout << "";
}
//*******