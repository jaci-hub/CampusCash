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
        }
        else puts("Connection to DataBase has failed");
}
//*******