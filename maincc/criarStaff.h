#pragma once
#include <iostream>
#include <string>
#include "file_com_pragmaonce_mysql.h"
using namespace std;

int qstateStaff;

//***Criacao do staff***
void criarStaff() {
    //Stablishing the connection to mysql database
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

    if (conn) {
        //simulation of log in into the schools platform 
        cout << "*** Campus Cash (CCash) ***" << "\n";
        //ckecking the staff's email
    tryStaffEmailagain:
        string check_email;
        bool check_email_val = false;
        cout << "*** Log in ***" << "\n";
        cout << "e-mail: ";
        cin >> check_email;
        string queryEmail = "SELECT * FROM staffdatatable";
        const char* qEmail = queryEmail.c_str();
        qstateStaff = mysql_query(conn, qEmail);
        if (!qstateStaff) {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res)) {
                if (check_email == row[1]) {
                    check_email_val = true;
                    break;
                }
            }
            if (check_email_val == false) {
                cout << "email not found!\n";
                goto tryStaffEmailagain;
            }
        }
        else cout << "Query failed: " << mysql_error(conn) << "\n";

        //ckecking the staff's password
    tryStaffPasswordagain:
        string check_password;
        cout << "password: ";
        cin >> check_password;
        string queryPassword = "SELECT staffPassword FROM staffdatatable WHERE staffEmail = '" + check_email + "'";
        const char* qPassword = queryPassword.c_str();
        qstateStaff = mysql_query(conn, qPassword);
        if (!qstateStaff) {
            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);
            if (check_password != row[0]) {
                cout << "password is incorrect!\n";
                goto tryStaffPasswordagain;
            }
        }
        else cout << "Query failed: " << mysql_error(conn) << "\n";
    }
    else puts("Connection to DataBase has failed");
}
//*******