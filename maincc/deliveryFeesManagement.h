#pragma once
#include <iostream>
#include <string>
#include "tableExists.h"
using namespace std;

int qstatedeliveryFeesManagement;

void deliveryFeesManagement() {
	//Stablishing the connection to mysql database
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

	if (conn) {
	inicio:
		//Create deliveryFeesTable if it doesnt exist already 
		if (tableExists("deliveryFeesTable") == false) {
			string queryCreateFeesTable = "CREATE TABLE deliveryFeesTable(feeName VARCHAR(255) NOT NULL UNIQUE, simplotcafe DOUBLE(5, 2) NOT NULL, mccaincenter DOUBLE(5, 2) NOT NULL)";
			const char* qCreateFeesTable = queryCreateFeesTable.c_str();
			qstatedeliveryFeesManagement = mysql_query(conn, qCreateFeesTable);
			if (qstatedeliveryFeesManagement)
				cout << "Query failed: " << mysql_error(conn) << "\n";

			//Inserting Variables
			string queryInsertValuesFeesTable = "INSERT INTO deliveryFeesTable(feeName, simplotcafe, mccaincenter) VALUES('ON campus Delivery Fee', 0, 0), ('OFF campus Delivery Fee', 0, 0)";
			const char* qInsertValuesFeesTable = queryInsertValuesFeesTable.c_str();
			qstatedeliveryFeesManagement = mysql_query(conn, qInsertValuesFeesTable);
			if (qstatedeliveryFeesManagement)
				cout << "Query failed: " << mysql_error(conn) << "\n";
		}
		cout << "* Select an option\n";
		cout << "d- Delivery fee\n";
		cout << "e- EXIT\n";
		cout << "Please, enter an option: ";
		string feeOption;
		cin >> feeOption;
			if (feeOption == "d") {
			theOnOffCampusDeliveryFee:
			//get ON campus delivery fee from DB and display it
			string onCampusDeliveryFee;
			string queryGettingonCampusDeliveryFee = "SELECT " + formatName(staff.get_foodBuilding()) + " FROM deliveryFeesTable WHERE feeName = 'ON campus Delivery Fee'";
			const char* qGettingonCampusDeliveryFee = queryGettingonCampusDeliveryFee.c_str();
			qstatedeliveryFeesManagement = mysql_query(conn, qGettingonCampusDeliveryFee);
			if (!qstatedeliveryFeesManagement) {
				res = mysql_store_result(conn);
				row = mysql_fetch_row(res);
				onCampusDeliveryFee = row[0];
			}

			//get OFF campus delivery fee from DB and display it
			string offCampusDeliveryFee;
			string queryGettingoffCampusDeliveryFee = "SELECT " + formatName(staff.get_foodBuilding()) + " FROM deliveryFeesTable WHERE feeName = 'OFF campus Delivery Fee'";
			const char* qGettingoffCampusDeliveryFee = queryGettingoffCampusDeliveryFee.c_str();
			qstatedeliveryFeesManagement = mysql_query(conn, qGettingoffCampusDeliveryFee);
			if (!qstatedeliveryFeesManagement) {
				res = mysql_store_result(conn);
				row = mysql_fetch_row(res);
				offCampusDeliveryFee = row[0];
			}

			else cout << "Query failed: " << mysql_error(conn) << "\n";
			cout << "** ON campus Delivery fee: " << onCampusDeliveryFee << "%\n";
			cout << "** OFF campus Delivery fee: " << offCampusDeliveryFee << "%\n\n";
			cout << "1- Update ON campus Delivery fee\n";
			cout << "2- Update OFF campus Delivery fee\n";
			cout << "b- Back\n";
			cout << "Please, enter an option: ";
			string onOffCampusDeliveryFeeOption;
			cin >> onOffCampusDeliveryFeeOption;

			if (onOffCampusDeliveryFeeOption == "1") {
				string newonCampusDeliveryFee;
				cout << "Fee(%): ";
				cin >> newonCampusDeliveryFee;

				//UPDATE onCampusDeliveryFee in DB
				string queryUpdateonCampusDeliveryFee = "UPDATE deliveryFeesTable SET " + formatName(staff.get_foodBuilding()) + " = " + newonCampusDeliveryFee + " WHERE feeName = 'ON campus Delivery Fee'";
				const char* qUpdateonCampusDeliveryFee = queryUpdateonCampusDeliveryFee.c_str();
				qstatedeliveryFeesManagement = mysql_query(conn, qUpdateonCampusDeliveryFee);
				if (qstatedeliveryFeesManagement)
					cout << "Query failed: " << mysql_error(conn) << "\n";

				goto theOnOffCampusDeliveryFee;
			}

			if (onOffCampusDeliveryFeeOption == "2") {
				string newoffCampusDeliveryFee;
				cout << "Fee(%): ";
				cin >> newoffCampusDeliveryFee;

				//UPDATE offCampusDeliveryFee in DB
				string queryUpdateoffCampusDeliveryFee = "UPDATE deliveryFeesTable SET " + formatName(staff.get_foodBuilding()) + " = " + newoffCampusDeliveryFee + " WHERE feeName = 'OFF campus Delivery Fee'";
				const char* qUpdateoffCampusDeliveryFee = queryUpdateoffCampusDeliveryFee.c_str();
				qstatedeliveryFeesManagement = mysql_query(conn, qUpdateoffCampusDeliveryFee);
				if (qstatedeliveryFeesManagement)
					cout << "Query failed: " << mysql_error(conn) << "\n";

				goto theOnOffCampusDeliveryFee;
			}

			else if (onOffCampusDeliveryFeeOption == "b")
				goto inicio;
		}

		else if (feeOption == "e") {
			goto deliveryFeesManagementEnd;
		}

		else feesManagement();
	}
	else puts("Connection to DataBase has failed");

deliveryFeesManagementEnd:
	cout << "";
}