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
        cout << "*** Campus Cash (CC) ***" << "\n";
        //ckecking the staff's email
    loginHere:
        string staffEmail, staffPassword;
        cout << "*** Log in ***" << "\n";
        cout << "e-mail: ";
        cin >> staffEmail;
        cout << "password: ";
        cin >> staffPassword;
        while (staffEmail != "jquimua@yotes.collegeofidaho.edu" && staffPassword != "ReinoDaMatamba11") {
            cout << "email or password is incorrect!\n";
            goto loginHere;
        }
    }
    else puts("Connection to DataBase has failed");
}
//*******