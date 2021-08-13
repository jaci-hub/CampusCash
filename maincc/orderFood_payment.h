#pragma once
#include <iostream>
#include <string>
#include "criar_sender.h"
#include "file_com_pragmaonce_mysql.h"
#include "orderPaymentFee.h"
#include "criar_orderFood.h"

using namespace std;

int qstateFoodPayment;

//****send_cash function***
void orderFood_payment() {
    //Stablishing the connection to mysql database
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

    if (conn) {
        cout << "*** Total: " << fixed << setprecision(2) << order1.get_foodOrderTotal() + orderPaymentFee() << "\n";
        cout << "* Placing order...\n\n";
        //Cafe - Pay with meals
        if (order1.selectedPlace == 1) {
        string queryEmail1 = "SELECT studentMeals FROM studentdatatable WHERE studentEmail = '" + student1.get_email() + "'";
        const char* qEmail1 = queryEmail1.c_str();
        qstateFoodPayment = mysql_query(conn, qEmail1);
        if (!qstateFoodPayment) {
            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);
            string oldMeal = row[0];
            int newMeal = stoi(oldMeal);
            newMeal -= 1;

            //Update student1 mealPlanBalance in classSender
            student1.mealPlanBalance = newMeal;

            //Update student1 mealPlanBalance in the DB
            string newMealString = to_string(newMeal);
            string querynewMeal1 = "UPDATE studentdatatable SET studentMeals = '" + newMealString + "' WHERE studentEmail = '" + student1.get_email() + "'";
            const char* qnewMeal1 = querynewMeal1.c_str();
            qstateFoodPayment = mysql_query(conn, qnewMeal1);
            if (qstateFoodPayment)
                cout << "Query failed: " << mysql_error(conn) << "\n";
        }
        else cout << "Query failed: " << mysql_error(conn) << "\n";

        //Display order message
        cout << "*** Campus Cash (CC)***" << "\n";
        cout << "* You are now #?? in line\n";
        }

            //McCain - pay with coyote cash
        else if(order1.selectedPlace == 2 && order1.paymentMethod == 2){
            string queryEmail1 = "SELECT studentBalance FROM studentdatatable WHERE studentEmail = '" + student1.get_email() + "'";
            const char* qEmail1 = queryEmail1.c_str();
            qstateFoodPayment = mysql_query(conn, qEmail1);
            if (!qstateFoodPayment) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                string oldCash = row[0];
                double newCash = stod(oldCash);
                newCash -= order1.get_foodOrderTotal() + orderPaymentFee();

                //Update student1 balance in classSender
                student1.balance = newCash;

                //Update student1 balance in the DB
                string newCashString = to_string(newCash);
                string querynewCash1 = "UPDATE studentdatatable SET studentBalance = '" + newCashString + "' WHERE studentEmail = '" + student1.get_email() + "'";
                const char* qnewCash1 = querynewCash1.c_str();
                qstateFoodPayment = mysql_query(conn, qnewCash1);
                if (qstateFoodPayment)
                    cout << "Query failed: " << mysql_error(conn) << "\n";
            }
            else cout << "Query failed: " << mysql_error(conn) << "\n";

            //Display order message
            cout << "*** Campus Cash (CC)***" << "\n";
            cout << "* You are now #?? in line\n"; 
        }

        //McCain - Pay with meals
        else if (order1.selectedPlace == 2 && order1.paymentMethod == 1) {
            string queryEmail1 = "SELECT studentMeals FROM studentdatatable WHERE studentEmail = '" + student1.get_email() + "'";
            const char* qEmail1 = queryEmail1.c_str();
            qstateFoodPayment = mysql_query(conn, qEmail1);
            if (!qstateFoodPayment) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                string oldMeal = row[0];
                int newMeal = stoi(oldMeal);
                newMeal -= 1;

                //Update student1 mealPlanBalance in classSender
                student1.mealPlanBalance = newMeal;

                //Update student1 mealPlanBalance in the DB
                string newMealString = to_string(newMeal);
                string querynewMeal1 = "UPDATE studentdatatable SET studentMeals = '" + newMealString + "' WHERE studentEmail = '" + student1.get_email() + "'";
                const char* qnewMeal1 = querynewMeal1.c_str();
                qstateFoodPayment = mysql_query(conn, qnewMeal1);
                if (qstateFoodPayment)
                    cout << "Query failed: " << mysql_error(conn) << "\n";
            }
            else cout << "Query failed: " << mysql_error(conn) << "\n";

            //Display order message
            cout << "*** Campus Cash (CC)***" << "\n";
            cout << "* You are now #?? in line\n"; 
        }
    }
    else puts("Connection to DataBase has failed");
}
//*******