#pragma once
#include<bits/stdc++.h>
#include "file_com_pragmaonce_mysql.h"
using namespace std;

int qstateListar;

void listarCoisas(string IDcolumn, string NameColumn, string nameOfTable) {
    //Stablishing the connection to mysql database
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

    if (conn) {
        int theID;
        string theName;
        string queryListarIDname = "SELECT " + IDcolumn + ", " + NameColumn + " FROM " + nameOfTable;
        const char* qListarIDname = queryListarIDname.c_str();
        qstateListar = mysql_query(conn, qListarIDname);
        if (!qstateListar) {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res)) {
                theID = stoi(row[0]);
                theName = row[1];
                cout << theID << "- " << theName << "\n";
            }
        }
        else cout << "Query failed: " << mysql_error(conn) << "\n";
    }
}