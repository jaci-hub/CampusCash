#pragma once
#include <iostream>
#include <string>
#include "file_com_pragmaonce_mysql.h"
using namespace std;

int qstateReceiver;
string receiversEmail, receiversName;

//***Criacao do receiver***
void criar_receiver() {
    //Stablishing the connection to mysql database
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

    if (conn) {
        cout << "*** Send to ***" << "\n"; 
        //ckecking the receiver's email
    tryRecEmailagain:
        string check_email;
        bool check_email_val = false;
        cout << "e-mail: ";
        cin >> check_email;
        //cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string queryEmail = "SELECT * FROM studentdatatable";
        const char* qEmail = queryEmail.c_str();
        qstateReceiver = mysql_query(conn, qEmail);
        if (!qstateReceiver) {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res)) {
                if (check_email == row[1] && check_email != student1.get_email()) { //PREVENT SENDER FROM SENDING TO THEMSELVES
                    check_email_val = true;
                    break;
                }
            }
            if (check_email_val == true)
                receiversEmail = check_email;
            else {
                cout << "email is inconvenient!\n";
                goto tryRecEmailagain;
            }
        }
        else cout << "Query failed: " << mysql_error(conn) << "\n";

            //ckecking the receiver's ID
        tryRecIDagain:
            string check_id;
            cout << "ID: ";
            cin >> check_id;
            //cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string queryID = "SELECT studentID FROM studentdatatable WHERE studentEmail = '" + receiversEmail + "'";
            const char* qID = queryID.c_str();
            qstateReceiver = mysql_query(conn, qID);
            if (!qstateReceiver) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                if (check_id != row[0]) {
                    cout << "ID is incorrect!\n";
                    goto tryRecIDagain;
                }
            }
            else cout << "Query failed: " << mysql_error(conn) << "\n";

            //setting Receiver name
            receiversName = "";
            for (int i = 0; i < receiversEmail.size(); i++) {
                if (receiversEmail[i] == '.') //specific to CofI email structure (firstname.lastname@...)
                    break;
                receiversName += receiversEmail[i];
            }
            receiversName[0] = toupper(receiversName[0]);
        }
        else puts("Connection to DataBase has failed");
}
//*******