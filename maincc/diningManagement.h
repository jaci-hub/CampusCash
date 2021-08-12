#pragma once
#include<bits/stdc++.h>
#include "file_com_pragmaonce_mysql.h"
#include "addCoisaToTable.h"
#include "removeCoisaFromTable.h"
#include "formatName.h"
#include "menuPlanManagement.h"
#include "getName_fromTable.h"
#include "buildingName_class.h"
#include "listarCoisas.h"
using namespace std;

int qstateManagement;

void diningManagement() {
	//Stablishing the connection to mysql database
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

	if (conn) {
		cout << "* Select an option \n";
		//listing the buildings in the foodBuildingsTable
		listarCoisas("foodBuildingID", "foodBuildingName", "foodBuildingsTable");

		//adding/removing a building options
		cout << "a- Add\n";
		cout << "r- Remove\n";
		cout << "Please, enter an option: ";
		string optionEscolhida1;
		cin >> optionEscolhida1;

		//heading to Menu Plan
		if (isdigit(optionEscolhida1[0]) != 0) {
			//Setting buildingName
			buildingName_class.buildingName = getName_fromTable("foodBuildingsTable", "foodBuildingName", "foodBuildingID", optionEscolhida1);
			//take out all spaces and lower-case all letters
			buildingName_class.buildingName = formatName(buildingName_class.buildingName);

			menuPlanManagement(); //from menuPlanManagement.h
		}

		//add
		else if (optionEscolhida1 == "a") {
			cout << "* Name of the new building: ";
			string newBuildingName;
			cin.ignore();
			getline(cin, newBuildingName);
			addCoisaToTable(newBuildingName, "foodBuilding", "foodBuildingsTable"); //ADDED

				//***criar table of orders da new building***//
			//take out all spaces and lower-case all letters
			newBuildingName = formatName(newBuildingName);

			string queryAddOrders = "CREATE TABLE " + newBuildingName + "OrdersTable" + "(studentEmail VARCHAR(255) NOT NULL, mealType VARCHAR(255) NOT NULL, the_food VARCHAR(255), the_drink VARCHAR(255), the_sides VARCHAR(255), otherFood VARCHAR(255), orderID INT KEY AUTO_INCREMENT, onOffCampus VARCHAR(10) NOT NULL, houseRoom VARCHAR(255) NOT NULL, totalAmount DOUBLE(5, 2) NOT NULL, feeApplied DOUBLE(5, 2) NOT NULL, transDateTime VARCHAR(255) NOT NULL)";
			const char* qAddOrders = queryAddOrders.c_str();
			qstateAdd = mysql_query(conn, qAddOrders);
			if (qstateAdd)
				cout << "Query failed: " << mysql_error(conn) << "\n";
		}

		//remove
		else if (optionEscolhida1 == "r") {
			cout << "* Select building to be removed\n";
			//listing the buildings in the foodBuildingsTable
			listarCoisas("foodBuildingID", "foodBuildingName", "foodBuildingsTable");

			cout << "Please, enter an option: ";
			int IDtobeRem;
			cin >> IDtobeRem;
			string NameTobeRem, IDtobeRemString = to_string(IDtobeRem);

			//Getting the food buildings name first
			NameTobeRem = getName_fromTable("foodBuildingsTable", "foodBuildingName", "foodBuildingID", IDtobeRemString);

			//Now removing the building
			removeCoisaFromTable(NameTobeRem, "foodBuildingName", "foodBuildingsTable"); //REMOVED

				//***dropping the table of orders da removed building***//
			//take out all spaces and lower-case all letters
			NameTobeRem = formatName(NameTobeRem);

			string queryRemOrders = "DROP TABLE " + NameTobeRem + "OrdersTable";
			const char* qRemOrders = queryRemOrders.c_str();
			qstateAdd = mysql_query(conn, qRemOrders);
			if (qstateAdd)
				cout << "Query failed: " << mysql_error(conn) << "\n";
		}
	}
	else puts("Connection to DataBase has failed");
}