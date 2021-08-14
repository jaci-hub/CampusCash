#pragma once
#include <iostream>
#include <string>
#include "file_com_pragmaonce_mysql.h"
#include "addCoisaToTable.h"
#include "removeCoisaFromTable.h"
#include "formatName.h"
#include "menuPlanManagement.h"
#include "getName_fromTable.h"
#include "allinOne_class.h"
#include "listarCoisas.h"
#include "dropTable.h"
using namespace std;

int qstateManagement;

void diningManagement() {
	//Stablishing the connection to mysql database
	MYSQL* conn;
	//MYSQL_ROW row;
	//MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

	if (conn) {
		cout << "* Select a building \n";
		//listing the buildings in the foodBuildingsTable
		listarCoisas("foodBuildingID", "foodBuildingName", "foodBuildingsTable");

		//adding/removing a building options
		cout << "a- Add\n";
		cout << "r- Remove\n";
		cout << "Please, enter an option: ";
		string optionEscolhida;
		cin >> optionEscolhida;

		//heading to Menu Plan
		if (isdigit(optionEscolhida[0]) != 0) {
			//Setting buildingName
			allinOne_class.buildingName = getName_fromTable("foodBuildingsTable", "foodBuildingName", "foodBuildingID", optionEscolhida);
			//take out all spaces and lower-case all letters
			allinOne_class.buildingName = formatName(allinOne_class.buildingName);

			menuPlanManagement(); //from menuPlanManagement.h
		}

		//add
		else if (optionEscolhida == "a") {
			cout << "* Name of the new building: ";
			string newBuildingName;
			cin.ignore();
			getline(cin, newBuildingName);
			addCoisaToTable(newBuildingName, "foodBuildingName", "foodBuildingsTable"); //ADDED

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
		else if (optionEscolhida == "r") {
			cout << "* Select building to be removed\n";
			//listing the buildings in the foodBuildingsTable
			listarCoisas("foodBuildingID", "foodBuildingName", "foodBuildingsTable");

			cout << "Please, enter an option: ";
			string NameTobeRem, IDtobeRem;
			cin >> IDtobeRem;

			//Getting the food buildings name first
			NameTobeRem = getName_fromTable("foodBuildingsTable", "foodBuildingName", "foodBuildingID", IDtobeRem);

			//Now removing the building
			removeCoisaFromTable(NameTobeRem, "foodBuildingName", "foodBuildingsTable"); //REMOVED

				//***dropping the table of orders da removed building***//
			//take out all spaces and lower-case all letters
			NameTobeRem = formatName(NameTobeRem);

			dropTable(NameTobeRem + "OrdersTable"); //TABLE DROPPED

				//ALSO DROP ALL THE OTHER TABLES RELATED TO THE REMOVED BUILDING
			//Drop "MenuPlanTable"
			//menuTableInUse = ? assign menuTableInUse appropriately!! it needs to be formed from the database somehow
			if(tableExists(menuTableInUse))
				dropTable(menuTableInUse);

			//Drop "categoryTable"
			//categoryTable = ? assign categoryTable appropriately!! it needs to be formed from the database somehow
			if (tableExists(CategoryTableName)) 
				dropTable(CategoryTableName);
			
			//Drop "ItemsTable"
			//ItemsTable = ? assign ItemsTable appropriately!! it needs to be formed from the database somehow
			if (tableExists(ItemsTableName)) 
				dropTable(ItemsTableName);
		}
	}
	else puts("Connection to DataBase has failed");
}