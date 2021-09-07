#pragma once
#include <iostream>
#include <string>
#include "file_com_pragmaonce_mysql.h"
#include "classStaff.h"

using namespace std;

int qstatePaymentMethods;

void paymentMethodsManagement() {
	//Stablishing the connection to mysql database
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

	if (conn) {
		displayPaymentMethods:
		string nomeDaBuilding;
		//selecting staff building
		string queryListarbuildings = "SELECT foodBuilding FROM staffDataTable WHERE staffEmail = '" + staff.get_email() + "'";
		const char* qListarbuildings = queryListarbuildings.c_str();
		qstatePaymentMethods = mysql_query(conn, qListarbuildings);
		if (!qstatePaymentMethods) {
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			nomeDaBuilding = row[0];
		}
		else cout << "Query failed: " << mysql_error(conn) << "\n";

		//display paymentMethod 1 & 2
		string paymentMethod1, paymentMethod2; //HAVE TO BE EITHER: Meals OR Cash!!!
		string queryListarpaymentMethods = "SELECT paymentMethod1, paymentMethod2 FROM foodBuildingsTable WHERE foodBuildingName = '" + nomeDaBuilding + "'";
		const char* qListarpaymentMethods = queryListarpaymentMethods.c_str();
		qstatePaymentMethods = mysql_query(conn, qListarpaymentMethods);
		if (!qstatePaymentMethods) {
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			paymentMethod1 = row[0];
			paymentMethod2 = row[1];
		}
		else cout << "Query failed: " << mysql_error(conn) << "\n";

		cout << "** " << nomeDaBuilding << " Payment methods **\n";
		cout << "* Select an option to update\n";
		cout << "1- Payment method 1: " << paymentMethod1 << "\n";
		cout << "2- Payment method 2: " << paymentMethod2 << "\n";
		cout << "b- Back\n";
		cout << "Please, enter an option: ";
		string paymentMethodOption;
		cin >> paymentMethodOption;

		if (paymentMethodOption == "b")
			goto paymentMethodsManagementEnd;
		//UPDATE paymentMethod1
		else if (paymentMethodOption == "1") {
			cout << "* Select a payment method\n";
			cout << "1- Meals\n";
			cout << "2- Cash\n";
			cout << "n- none\n";
			cout << "b- Back\n";
			cout << "Please, enter an option: ";
			string payMchoice;
			cin >> payMchoice;
			if (payMchoice == "b")
				goto displayPaymentMethods;
			else if (payMchoice == "1") {
				string querySetpay1 = "UPDATE foodBuildingsTable SET paymentMethod1 = 'Meals' WHERE foodBuildingName = '" + nomeDaBuilding + "'";
				const char* qSetpay1 = querySetpay1.c_str();
				qstatePaymentMethods = mysql_query(conn, qSetpay1);
				if (qstatePaymentMethods)
					cout << "Query failed: " << mysql_error(conn) << "\n";

				goto displayPaymentMethods;
			}
			else if (payMchoice == "2") {
				string querySetpay1 = "UPDATE foodBuildingsTable SET paymentMethod1 = 'Cash' WHERE foodBuildingName = '" + nomeDaBuilding + "'";
				const char* qSetpay1 = querySetpay1.c_str();
				qstatePaymentMethods = mysql_query(conn, qSetpay1);
				if (qstatePaymentMethods)
					cout << "Query failed: " << mysql_error(conn) << "\n";

				goto displayPaymentMethods;
			}
			else if (payMchoice == "n") {
				string querySetpay1 = "UPDATE foodBuildingsTable SET paymentMethod1 = 'none' WHERE foodBuildingName = '" + nomeDaBuilding + "'";
				const char* qSetpay1 = querySetpay1.c_str();
				qstatePaymentMethods = mysql_query(conn, qSetpay1);
				if (qstatePaymentMethods)
					cout << "Query failed: " << mysql_error(conn) << "\n";

				goto displayPaymentMethods;
			}
		}
		//UPDATE paymentMethod2
		else if (paymentMethodOption == "2") {
			cout << "* Select a payment method\n";
			cout << "1- Meals\n";
			cout << "2- Cash\n";
			cout << "n- none\n";
			cout << "b- Back\n";
			cout << "Please, enter an option: ";
			string payMchoice;
			cin >> payMchoice;
			if (payMchoice == "b")
				goto displayPaymentMethods;
			else if (payMchoice == "1") {
				string querySetpay1 = "UPDATE foodBuildingsTable SET paymentMethod2 = 'Meals' WHERE foodBuildingName = '" + nomeDaBuilding + "'";
				const char* qSetpay1 = querySetpay1.c_str();
				qstatePaymentMethods = mysql_query(conn, qSetpay1);
				if (qstatePaymentMethods)
					cout << "Query failed: " << mysql_error(conn) << "\n";

				goto displayPaymentMethods;
			}
			else if (payMchoice == "2") {
				string querySetpay1 = "UPDATE foodBuildingsTable SET paymentMethod2 = 'Cash' WHERE foodBuildingName = '" + nomeDaBuilding + "'";
				const char* qSetpay1 = querySetpay1.c_str();
				qstatePaymentMethods = mysql_query(conn, qSetpay1);
				if (qstatePaymentMethods)
					cout << "Query failed: " << mysql_error(conn) << "\n";

				goto displayPaymentMethods;
			}
			else if (payMchoice == "n") {
				string querySetpay1 = "UPDATE foodBuildingsTable SET paymentMethod2 = 'none' WHERE foodBuildingName = '" + nomeDaBuilding + "'";
				const char* qSetpay1 = querySetpay1.c_str();
				qstatePaymentMethods = mysql_query(conn, qSetpay1);
				if (qstatePaymentMethods)
					cout << "Query failed: " << mysql_error(conn) << "\n";

				goto displayPaymentMethods;
			}
		}
	}
	else puts("Connection to DataBase has failed");

paymentMethodsManagementEnd:
	cout << "";
}