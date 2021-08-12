#pragma once
#include<bits/stdc++.h>
#include "file_com_pragmaonce_mysql.h"
using namespace std;

int qstateAdd;

void addCoisaToTable(string nomeDaCoisa, string nomeDaColuna, string nomeDaTable) {
	//Stablishing the connection to mysql database
	MYSQL* conn;
	//MYSQL_ROW row;
	//MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

	if (conn) {
		string queryAdd = "INSERT INTO " + nomeDaTable + "(" + nomeDaColuna + ") VALUE('" + nomeDaCoisa + "')";
		const char* qAdd = queryAdd.c_str();
		qstateAdd = mysql_query(conn, qAdd);
		if (!qstateAdd)
			cout << "** " << nomeDaCoisa << " added!\n";
		else cout << "Query failed: " << mysql_error(conn) << "\n";
	}
	else puts("Connection to DataBase has failed");
}