#pragma once
#include <iostream>
#include <string>
#include "tableExists.h"
using namespace std;

int qstateFeeManagement;

void feesManagement() {
	//Stablishing the connection to mysql database
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

	if (conn) {
		inicio:
		//Create feesTable if it doesnt exist already 
		if (tableExists("feesTable") == false) {
			string queryCreateFeesTable = "CREATE TABLE feesTable(feeName VARCHAR(255) NOT NULL UNIQUE, PercentageFee DOUBLE(5, 2) NOT NULL)";
			const char* qCreateFeesTable = queryCreateFeesTable.c_str();
			qstateFeeManagement = mysql_query(conn, qCreateFeesTable);
			if (qstateFeeManagement)
				cout << "Query failed: " << mysql_error(conn) << "\n";

			//Inserting Variables
			string queryInsertValuesFeesTable = "INSERT INTO feesTable(feeName, PercentageFee) VALUES('Meal Transaction Fee', 0), ('Cash Transaction Fee', 0)";
			const char* qInsertValuesFeesTable = queryInsertValuesFeesTable.c_str();
			qstateFeeManagement = mysql_query(conn, qInsertValuesFeesTable);
			if (qstateFeeManagement)
				cout << "Query failed: " << mysql_error(conn) << "\n";
		}
		cout << "* Select an option\n";
		cout << "t- Transaction fee\n";
		cout << "e- EXIT\n";
		cout << "Please, enter an option: ";
		string feeOption;
		cin >> feeOption;

		if (feeOption == "t") {
		theTransactionFee:
			//get Meal transaction fee from DB and display it
			string mealTransactionFee;
			string queryGettingmealTransactionFee = "SELECT PercentageFee FROM feesTable WHERE feeName = 'Meal Transaction Fee'";
			const char* qGettingmealTransactionFee = queryGettingmealTransactionFee.c_str();
			qstateFeeManagement = mysql_query(conn, qGettingmealTransactionFee);
			if (!qstateFeeManagement) {
				res = mysql_store_result(conn);
				row = mysql_fetch_row(res);
				mealTransactionFee = row[0];
			}

			//get Cash transaction fee from DB and display it
			string cashTransactionFee;
			string queryGettingcashTransactionFee = "SELECT PercentageFee FROM feesTable WHERE feeName = 'Cash Transaction Fee'";
			const char* qGettingcashTransactionFee = queryGettingcashTransactionFee.c_str();
			qstateFeeManagement = mysql_query(conn, qGettingcashTransactionFee);
			if (!qstateFeeManagement) {
				res = mysql_store_result(conn);
				row = mysql_fetch_row(res);
				cashTransactionFee = row[0];
			}

			else cout << "Query failed: " << mysql_error(conn) << "\n";
			cout << "** Meal Transaction Fee: " << mealTransactionFee << "%\n";
			cout << "** Cash Transaction Fee: " << cashTransactionFee << "%\n\n";
			cout << "1- Update Meal Transaction Fee\n";
			cout << "2- Update Cash Transaction Fee\n";
			cout << "b- Back\n";
			cout << "Please, enter an option: ";
			string TransactionFeeOption;
			cin >> TransactionFeeOption;

			if (TransactionFeeOption == "1") {
				string newmealTransactionFee;
				cout << "Fee(%): ";
				cin >> newmealTransactionFee;

				//UPDATE Meal Transaction Fee in DB
				string queryUpdatemealTransactionFee = "UPDATE feesTable SET PercentageFee = " + newmealTransactionFee + " WHERE feeName = 'Meal Transaction Fee'";
				const char* qUpdatemealTransactionFee = queryUpdatemealTransactionFee.c_str();
				qstateFeeManagement = mysql_query(conn, qUpdatemealTransactionFee);
				if (qstateFeeManagement)
					cout << "Query failed: " << mysql_error(conn) << "\n";

				goto theTransactionFee;
			}

			if (TransactionFeeOption == "2") {
				string newcashTransactionFee;
				cout << "Fee(%): ";
				cin >> newcashTransactionFee;

				//UPDATE Cash Transaction Fee in DB
				string queryUpdatecashTransactionFee = "UPDATE feesTable SET PercentageFee = " + newcashTransactionFee + " WHERE feeName = 'Cash Transaction Fee'";
				const char* qUpdatecashTransactionFee = queryUpdatecashTransactionFee.c_str();
				qstateFeeManagement = mysql_query(conn, qUpdatecashTransactionFee);
				if (qstateFeeManagement)
					cout << "Query failed: " << mysql_error(conn) << "\n";

				goto theTransactionFee;
			}

			else if (TransactionFeeOption == "b")
				goto inicio;
		}
		else if (feeOption == "e") {
			goto feesManagementEnd;
		}

		else feesManagement();
	}
	else puts("Connection to DataBase has failed");

feesManagementEnd:
	cout << "";
}