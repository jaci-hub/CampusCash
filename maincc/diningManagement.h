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
#include "foodBuildingExists.h"
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
	listaDasFoodBuildings:
		//Create foodBuildingsTable if it doesnt exist yet
		if (tableExists("foodBuildingsTable") == false) {
			string queryCriarTable = "CREATE TABLE foodBuildingsTable(foodBuildingName VARCHAR(255) NOT NULL, foodBuildingID INT KEY AUTO_INCREMENT)";
			const char* qCriarTable = queryCriarTable.c_str();
			qstateManagement = mysql_query(conn, qCriarTable);
			if (qstateManagement)
				cout << "Query failed: " << mysql_error(conn) << "\n";
		}

		cout << "* Select building \n";
		string nomeDaBuilding;
		//listing the buildings in the foodBuildingsTable
		string queryListarbuildings = "SELECT foodBuilding FROM staffDataTable WHERE staffEmail = '" + staff.get_email() + "'";
		const char* qListarbuildings = queryListarbuildings.c_str();
		qstateManagement = mysql_query(conn, qListarbuildings);
		if (!qstateManagement) {
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			if (row[0] != "none")
				cout << "s- " << row[0] << "\n";
			nomeDaBuilding = row[0];
		}
		else cout << "Query failed: " << mysql_error(conn) << "\n";

		//adding/removing a building options
		if(nomeDaBuilding == "none")
			cout << "a- Add (NOTE: This will assign you a new building!)\n";
		if (nomeDaBuilding != "none")
			cout << "r- Remove (NOTE: This will remove the building and its workers from all records permanently!)\n";
		cout << "b- Back\n";
		cout << "Please, enter an option: ";
		string optionEscolhida;
		cin >> optionEscolhida;

		//heading to Menu Plan
		if (optionEscolhida == "s") {
			//Setting buildingName
			allinOne_class.buildingName = nomeDaBuilding;
			//take out all spaces and lower-case all letters
			allinOne_class.buildingName = formatName(allinOne_class.buildingName);

			menuPlanManagement(); //from menuPlanManagement.h
		}

		//add
		else if (optionEscolhida == "a") {
			nomeDeNovo:
			cout << "* Name: ";
			string newBuildingName;
			cin.ignore();
			getline(cin, newBuildingName);
			if (newBuildingName == "None" || newBuildingName == "none") {//so it doesnt conflict with buildingOrderedFrom in studentDataTable when first initialized!
				cout << "* Invalid!";
				goto nomeDeNovo;
			}
			else if (foodBuildingExists(newBuildingName) == true) {
				cout << "* Building already exists!";
				goto nomeDeNovo;
			}
			else addCoisaToTable(newBuildingName, "foodBuildingName", "foodBuildingsTable"); //ADDED

			//Assign building to the manager in staffDataTable under foodBuilding
			string queryUpdatefoodBuilding = "UPDATE staffDataTable SET foodBuilding = '" + newBuildingName + "' WHERE staffEmail = '" + staff.get_email() + "'";
			const char* qUpdatefoodBuilding = queryUpdatefoodBuilding.c_str();
			qstateManagement = mysql_query(conn, qUpdatefoodBuilding);
			if (qstateManagement)
				cout << "Query failed: " << mysql_error(conn) << "\n";

			//take out all spaces and lower-case all letters
			newBuildingName = formatName(newBuildingName);

			//***criar table of orders da new building***//
			string queryAddOrders = "CREATE TABLE " + newBuildingName + "OrdersTable(orderID INT KEY AUTO_INCREMENT, studentEmail VARCHAR(255) NOT NULL, diet VARCHAR(255) NOT NULL, meal VARCHAR(255), sideOne VARCHAR(255), sideTwo VARCHAR(255), sideThree VARCHAR(255), onOffCampus VARCHAR(10) NOT NULL, dorm VARCHAR(255) NOT NULL, roomNumber VARCHAR(10) NOT NULL, subTotal DOUBLE(5, 2) NOT NULL, deliveryFee DOUBLE(5, 2) NOT NULL, paymentMethod VARCHAR(255) NOT NULL, orderDateTime VARCHAR(255) NOT NULL)";
			const char* qAddOrders = queryAddOrders.c_str();
			qstateManagement = mysql_query(conn, qAddOrders);
			if (qstateManagement)
				cout << "Query failed: " << mysql_error(conn) << "\n";

			//Create workingTimesTable
			string queryCriarfoodBuildingsTimesTable = "CREATE TABLE " + newBuildingName + "WorkingTimesTable(dayName VARCHAR(255) NOT NULL, openingTime VARCHAR(255) NOT NULL, closingTime VARCHAR(255) NOT NULL)";
			const char* qCriarfoodBuildingsTimesTable = queryCriarfoodBuildingsTimesTable.c_str();
			qstateManagement = mysql_query(conn, qCriarfoodBuildingsTimesTable);
			if (qstateManagement)
				cout << "Query failed: " << mysql_error(conn) << "\n";

			//Insert days workingTimesTable
			string queryAddDays = "INSERT INTO " + newBuildingName + "WorkingTimesTable(dayName, openingTime, closingTime) VALUES('Sunday', 'none', 'none'), ('Monday', 'none', 'none'), ('Tuesday', 'none', 'none'), ('Wednesday', 'none', 'none'), ('Thursday', 'none', 'none'), ('Friday', 'none', 'none'), ('Saturday', 'none', 'none')";
			const char* qAddDays = queryAddDays.c_str();
			qstateManagement = mysql_query(conn, qAddDays);
			if (qstateManagement)
				cout << "Query failed: " << mysql_error(conn) << "\n";

			//***criar MCID - MenuPlan, Category, Items and Diet - record table***//
			if (tableExists("MCIDrecordTable") == false) {
				string queryMCID = "CREATE TABLE MCIDrecordTable(MenuPlanTables VARCHAR(255), CategoryTables VARCHAR(255), ItemsTables VARCHAR(255), DietTables VARCHAR(255))";
				const char* qMCID = queryMCID.c_str();
				qstateManagement = mysql_query(conn, qMCID);
				if (qstateManagement)
					cout << "Query failed: " << mysql_error(conn) << "\n";
			}

			goto listaDasFoodBuildings;
		}

		//remove
		else if (optionEscolhida == "r") {
			cout << "* Select building to be removed\n";
			//listing the buildings in the foodBuildingsTable
			string queryListarbuildings = "SELECT foodBuilding FROM staffDataTable WHERE staffEmail = '" + staff.get_email() + "'";
			const char* qListarbuildings = queryListarbuildings.c_str();
			qstateManagement = mysql_query(conn, qListarbuildings);
			if (!qstateManagement) {
				res = mysql_store_result(conn);
				row = mysql_fetch_row(res);
				if (row[0] != "none")
					cout << "s- " << row[0] << "\n";
				cout << "b- Back\n";
				nomeDaBuilding = row[0];
			}
			else cout << "Query failed: " << mysql_error(conn) << "\n";

			cout << "Please, enter an option: ";
			string NameTobeRem, IDtobeRem;
			cin >> IDtobeRem;

			if (IDtobeRem == "s") {
				//Getting the food buildings name first
				NameTobeRem = nomeDaBuilding;

				//Now removing the building
				removeCoisaFromTable(NameTobeRem, "foodBuildingName", "foodBuildingsTable"); //REMOVED

				//Set manager foodbuilding to 'none'
				string querySetfoodBuilding = "UPDATE staffDataTable SET foodBuilding = 'none' WHERE staffEmail = '" + staff.get_email() + "'";
				const char* qSetfoodBuilding = querySetfoodBuilding.c_str();
				qstateManagement = mysql_query(conn, qSetfoodBuilding);
				if (qstateManagement)
					cout << "Query failed: " << mysql_error(conn) << "\n";

				//Since it takes time to take all this tables down, then display this message
				cout << "* Just a moment...\n";

				bool thereAreOthers = false;
				string queryListarOthers = "SELECT staffEmail FROM staffDataTable WHERE foodBuilding = '" + NameTobeRem + "'";
				const char* qListarOthers = queryListarOthers.c_str();
				qstateManagement = mysql_query(conn, qListarOthers);
				if (!qstateManagement) {
					res = mysql_store_result(conn);
					while (row = mysql_fetch_row(res))
						thereAreOthers = true;
				}
				else cout << "Query failed: " << mysql_error(conn) << "\n";

				//remove everyone (but the current manager of course) from staffDataTable with this foodBuilding - NOTE: the current manager needs to add the other managers after if necessary
				if (thereAreOthers == true) {
					string queryRemAll = "DELETE FROM staffDataTable WHERE foodBuilding = '" + NameTobeRem + "' AND staffEmail != '" + staff.get_email() + "'";
					const char* qRemAll = queryRemAll.c_str();
					qstateManagement = mysql_query(conn, qRemAll);
					if (qstateManagement)
						cout << "Query failed: " << mysql_error(conn) << "\n";
				}

				//take out all spaces and lower-case all letters
				NameTobeRem = formatName(NameTobeRem);

				//***dropping the table of orders da removed building***//
				dropTable(NameTobeRem + "OrdersTable"); //TABLE DROPPED

				//***dropping the WorkingTimesTable da removed building***//
				dropTable(NameTobeRem + "WorkingTimesTable"); //TABLE DROPPED

				if (tableExists(NameTobeRem + "MealsTimeAndPrice") == true) {
					//***dropping the mealsTimeAndPrice table da removed building***//
					dropTable(NameTobeRem + "MealsTimeAndPrice"); //TABLE DROPPED
				}

				//ALSO DROP ALL THE OTHER TABLES RELATED TO THE REMOVED BUILDING
			//Drop "MenuPlanTable"
				string queryDropMenuPlanTable = "SELECT * FROM MCIDrecordTable WHERE MenuPlanTables LIKE '%" + NameTobeRem + "MenuPlanTable" + "%'";
				const char* qDropMenuPlanTable = queryDropMenuPlanTable.c_str();
				qstateMenuPlanManagement = mysql_query(conn, qDropMenuPlanTable);
				if (!qstateMenuPlanManagement) {
					res = mysql_store_result(conn);
					while (row = mysql_fetch_row(res)) {
						if (tableExists(row[0]))
							dropTable(row[0]);
					}
				}
				else cout << "Query failed: " << mysql_error(conn) << "\n";

				//Drop "CategoryTable"
				string queryDropCategoryTable = "SELECT * FROM MCIDrecordTable WHERE CategoryTables LIKE '%" + NameTobeRem + "CategoryTable%'";
				const char* qDropCategoryTable = queryDropCategoryTable.c_str();
				qstateMenuPlanManagement = mysql_query(conn, qDropCategoryTable);
				if (!qstateMenuPlanManagement) {
					res = mysql_store_result(conn);
					while (row = mysql_fetch_row(res)) {
						if (tableExists(row[1]))
							dropTable(row[1]);
					}
				}
				else cout << "Query failed: " << mysql_error(conn) << "\n";

				//Drop "ItemsTable"
				string queryDropItemsTable = "SELECT * FROM MCIDrecordTable WHERE ItemsTables LIKE '%" + NameTobeRem + "ItemsTable" + "%'";
				const char* qDropItemsTable = queryDropItemsTable.c_str();
				qstateMenuPlanManagement = mysql_query(conn, qDropItemsTable);
				if (!qstateMenuPlanManagement) {
					res = mysql_store_result(conn);
					while (row = mysql_fetch_row(res)) {
						if (tableExists(row[2]))
							dropTable(row[2]);
					}
				}
				else cout << "Query failed: " << mysql_error(conn) << "\n";

				//Drop "DietTable"
				string queryDropDietTable = "SELECT * FROM MCIDrecordTable WHERE DietTables LIKE '%" + NameTobeRem + "DietTable" + "%'";
				const char* qDropDietTable = queryDropDietTable.c_str();
				qstateMenuPlanManagement = mysql_query(conn, qDropDietTable);
				if (!qstateMenuPlanManagement) {
					res = mysql_store_result(conn);
					while (row = mysql_fetch_row(res)) {
						if (tableExists(row[3]))
							dropTable(row[3]);
					}
				}
				else cout << "Query failed: " << mysql_error(conn) << "\n";

				//***Removing all records related to the table from MCIDrecordTable
			//MenuPlanTables
				string queryRemMenuPlanTables = "DELETE FROM MCIDrecordTable WHERE MenuPlanTables LIKE '%" + NameTobeRem + "%'";
				const char* qRemMenuPlanTables = queryRemMenuPlanTables.c_str();
				qstateRem = mysql_query(conn, qRemMenuPlanTables);
				if (qstateRem)
					cout << "Query failed: " << mysql_error(conn) << "\n";

				//CategoryTables
				string queryRemCategoryTables = "DELETE FROM MCIDrecordTable WHERE CategoryTables LIKE '%" + NameTobeRem + "%'";
				const char* qRemCategoryTables = queryRemCategoryTables.c_str();
				qstateRem = mysql_query(conn, qRemCategoryTables);
				if (qstateRem)
					cout << "Query failed: " << mysql_error(conn) << "\n";

				//ItemsTables
				string queryRemItemsTables = "DELETE FROM MCIDrecordTable WHERE ItemsTables LIKE '%" + NameTobeRem + "%'";
				const char* qRemItemsTables = queryRemItemsTables.c_str();
				qstateRem = mysql_query(conn, qRemItemsTables);
				if (qstateRem)
					cout << "Query failed: " << mysql_error(conn) << "\n";

				//DietTables
				string queryRemDietTables = "DELETE FROM MCIDrecordTable WHERE DietTables LIKE '%" + NameTobeRem + "%'";
				const char* qRemDietTables = queryRemDietTables.c_str();
				qstateRem = mysql_query(conn, qRemDietTables);
				if (qstateRem)
					cout << "Query failed: " << mysql_error(conn) << "\n";

				goto listaDasFoodBuildings;
			}
			else if(IDtobeRem == "b")
				goto listaDasFoodBuildings;
		}

		else if (optionEscolhida == "b")
			goto diningManagementEnd;
	}
	else puts("Connection to DataBase has failed");

diningManagementEnd:
	cout << "";
}