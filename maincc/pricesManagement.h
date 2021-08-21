#pragma once
#include <iostream>
#include <string>
using namespace std;

int qstatepricesManagement;

void pricesManagement() {
	//Stablishing the connection to mysql database
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

	if (conn) {
	theBuildings:
		cout << "* Select a building \n";
		//listing the buildings in the foodBuildingsTable
		listarCoisas("foodBuildingID", "foodBuildingName", "foodBuildingsTable");

		cout << "e- EXIT\n";
		cout << "Please, enter an option: ";
		string escolha;
		cin >> escolha;

		if (isdigit(escolha[0]) != 0) {
		theMeals:
			string buildingName = getName_fromTable("foodBuildingsTable", "foodBuildingName", "foodBuildingID", escolha);
			buildingName = formatName(buildingName);
			cout << "* Select meal \n";
			//listing the meals in the MealsTimeAndPrice
			listarCoisas("mealID", "meal", buildingName + "MealsTimeAndPrice");
			cout << "5- Other\n";
			cout << "b- Back\n";
			cout << "Please, enter an option: ";
			string mealSelected;
			cin >> mealSelected;

			if (stoi(mealSelected) >= 1 && stoi(mealSelected) <= 4) {
			selectedMeal:
				string mealName = getName_fromTable(buildingName + "MealsTimeAndPrice", "meal", "mealID", mealSelected);

				//***Display meal price//
				string price = getName_fromTable(buildingName + "MealsTimeAndPrice", "price", "meal", mealName);

				cout << "* " << mealName << ": $" << price << "\n\n";
				cout << "* Select an option\n";
				cout << "1- Update price\n";
				cout << "b- Back\n";
				cout << "Please, enter an option: ";
				string option;
				cin >> option;
				if (option == "1") {
					//update price
					cout << "Price: ";
					double newPrice;
					cin >> newPrice;
					string newPriceString = to_string(newPrice);
					string queryUpdatePrice = "UPDATE " + buildingName + "MealsTimeAndPrice SET price = " + newPriceString + " WHERE meal = '" + mealName + "'";
					const char* qUpdatePrice = queryUpdatePrice.c_str();
					qstatepricesManagement = mysql_query(conn, qUpdatePrice);
					if (qstatepricesManagement)
						cout << "Query failed: " << mysql_error(conn) << "\n";

					goto selectedMeal;
				}
				else if (option == "b")
					goto theMeals;
			}
			//other
			else if (mealSelected == "5") {
			listaDasCategorias:
				//display building category table
				cout << "* Select a category \n";
				//if tableExists
				//listing the categories in the CategoryTableName
				//listarCoisas("categoryID", "categoryName", mealtype here!!! buildingName + "CategoryTable");

				cout << "b- Back\n";
				cout << "Please, enter an option: ";
				string categoryOption;
				cin >> categoryOption;

				if (isdigit(categoryOption[0]) != 0) {
				listaDosItems:
					string categoryName;
					//Setting categoryName
					categoryName = getName_fromTable(buildingName + "CategoryTable", "categoryName", "categoryID", categoryOption);

					//take out all spaces and lower-case all letters
					categoryName = formatName(categoryName);

					cout << "* Prices for " + getName_fromTable(buildingName + "CategoryTable", "categoryName", "categoryID", categoryOption) + ": \n";
					//listing categoryName table selected with prices
					int theID;
					string theName;
					double theprice;
					string queryListarIDnamePrice = "SELECT itemID, itemName, price FROM " + categoryName + buildingName + "ItemsTable";
					const char* qListarIDnamePrice = queryListarIDnamePrice.c_str();
					qstatepricesManagement = mysql_query(conn, qListarIDnamePrice);
					if (!qstatepricesManagement) {
						res = mysql_store_result(conn);
						while (row = mysql_fetch_row(res)) {
							theID = stoi(row[0]);
							theName = row[1];
							theprice = stod(row[3]);
							cout << theID << "- " << theName << ": $" << theprice << "\n";
						}
					}
					else cout << "Query failed: " << mysql_error(conn) << "\n";

					cout << "1- Update price\n";
					cout << "b- Back to categories\n";
					cout << "Please, enter an option: ";
					string itemOption;
					cin >> itemOption;

					if (isdigit(itemOption[0]) != 0) {
						//update price of item

						goto listaDosItems;
					}
					else if (itemOption == "b")
						goto listaDasCategorias;
				}
				else if (categoryOption == "b")
					goto theMeals;
			}
			else if (mealSelected == "b") //WHY IS THIS NOT WORKING???
				goto theBuildings;
		}
		else if (escolha == "e")
			goto pricesManagementEnd;
	}
	else puts("Connection to DataBase has failed");

pricesManagementEnd:
	cout << "";
}