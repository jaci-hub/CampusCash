#pragma once
#include <iostream>
#include <string>
#include "file_com_pragmaonce_mysql.h"
using namespace std;

int qstateRem;

void removeCoisaFromTable(string nomeDaCoisa, string nomeDaColuna, string nomeDaTable) {
	//Stablishing the connection to mysql database
	MYSQL* conn;
	//MYSQL_ROW row;
	//MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

	if (conn) {
		string queryRem = "DELETE FROM " + nomeDaTable + " WHERE " + nomeDaColuna + " = '" + nomeDaCoisa + "'";
		const char* qRem = queryRem.c_str();
		qstateRem = mysql_query(conn, qRem);
		if (!qstateRem)
			cout <<"** "<< nomeDaCoisa << " removed!\n";
		else cout << "Query failed: " << mysql_error(conn) << "\n";
	}
	else puts("Connection to DataBase has failed");
}