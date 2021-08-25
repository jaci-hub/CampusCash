#pragma once
#include <iostream>
#include <string>
#include "classSender.h"
#include "file_com_pragmaonce_mysql.h"
using namespace std;

int qstateSender;

//***Criacao do sender***
void criar_sender() {
    //Stablishing the connection to mysql database
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

    if (conn) {
        //simulation of log in into the schools platform 
        cout << "*** Campus Cash (CC) ***" << "\n";
        //ckecking the sender's email
    trySenEmailagain:
        string check_email;
        bool check_email_val = false;
        cout << "*** Log in ***" << "\n";
        cout << "e-mail: ";
        cin >> check_email;
        //cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string queryEmail = "SELECT * FROM studentdatatable";
        const char* qEmail = queryEmail.c_str();
        qstateSender = mysql_query(conn, qEmail);
        if (!qstateSender) {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res)) {
                if (check_email == row[1]) {
                    check_email_val = true;
                    break;
                }
            }
            if (check_email_val == true)
                student1.email = check_email;
            else {
                cout << "email not found!\n";
                goto trySenEmailagain;
            }
        }
        else cout << "Query failed: " << mysql_error(conn) << "\n";

            //ckecking the sender's password
        trySenPasswordagain:
            string check_password;
            cout << "password: ";
            cin >> check_password;
            //cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string queryPassword = "SELECT studentPassword FROM studentdatatable WHERE studentEmail = '" + student1.email + "'";
            const char* qPassword = queryPassword.c_str();
            qstateSender = mysql_query(conn, qPassword);
            if (!qstateSender) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                if (check_password != row[0]) {
                    cout << "password is incorrect!\n";
                    goto trySenPasswordagain;
                }
            }
            else cout << "Query failed: " << mysql_error(conn) << "\n";

            //SETTING THE OTHER VARIABLES FOR SENDER/STUDENT1

            //setting name
            for (int i = 0; i < student1.email.size(); i++) {
                if (student1.email[i] == '.') //specific to CofI email structure (firstname.lastname@...)
                    break;
                student1.name += student1.email[i];
            }
            student1.name[0] = toupper(student1.name[0]);

            //setting ID
            string queryID = "SELECT studentID FROM studentdatatable WHERE studentEmail = '" + student1.email + "'";
            const char* qID = queryID.c_str();
            qstateSender = mysql_query(conn, qID);
            if (!qstateSender) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                student1.id = stoi(row[0]);
            }
            else cout << "Query failed: " << mysql_error(conn) << "\n";

            //setting balance
            string queryBalance = "SELECT studentBalance FROM studentdatatable WHERE studentEmail = '" + student1.email + "'";
            const char* qBalance = queryBalance.c_str();
            qstateSender = mysql_query(conn, qBalance);
            if (!qstateSender) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                student1.balance = stod(row[0]);
            }
            else cout << "Query failed: " << mysql_error(conn) << "\n";

            //setting mealPlanBalance
            string queryMeal = "SELECT studentMeals FROM studentdatatable WHERE studentEmail = '" + student1.email + "'";
            const char* qMeal = queryMeal.c_str();
            qstateSender = mysql_query(conn, qMeal);
            if (!qstateSender) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                student1.mealPlanBalance = stoi(row[0]);
            }
            else cout << "Query failed: " << mysql_error(conn) << "\n";
        }
        else puts("Connection to DataBase has failed");
}
//*******