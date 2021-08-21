#pragma once
#include <iostream>
#include <string>
#include "tableExists.h"
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
		if (tableExists("foodBuildingsTable") == true)
			listarCoisas("foodBuildingID", "foodBuildingName", "foodBuildingsTable");
		else cout << "*No building!\n";

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
			if (tableExists(buildingName + "MealsTimeAndPrice") == true)
				listarCoisas("mealID", "meal", buildingName + "MealsTimeAndPrice");
			else cout << "*No meal!\n";
			cout << "5- Other\n";

			cout << "b- Back\n"; 
			cout << "Please, enter an option: ";
			string mealSelected;
			cin >> mealSelected;

			//Back to theBuildings
			if (mealSelected == "b")
				goto theBuildings;

			if (stoi(mealSelected) >= 1 && stoi(mealSelected) <= 4) {
			selectedMeal:
				string mealName = getName_fromTable(buildingName + "MealsTimeAndPrice", "meal", "mealID", mealSelected);

				//***Display meal price//
				string price = getName_fromTable(buildingName + "MealsTimeAndPrice", "price", "meal", mealName);

				cout << "* " << mealName << ": $" << price << "\n\n";
				cout << "* Select an option\n";
				cout << "u- Update price\n";
				cout << "b- Back\n";
				cout << "Please, enter an option: ";
				char option;
				cin >> option;
				if (option == 'u') {
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
				else if (option == 'b')
					goto theMeals;
			}
			//other
			else if (mealSelected == "5") {
			theDiets:
				cout << "* Select a diet\n";
				//listar as diets from buildingName + "DietTable"
				if (tableExists(buildingName + "DietTable") == true)
					listarCoisas("dietID", "dietName", buildingName + "DietTable");
				else cout << "* No diet!\n";

				cout << "b- Back\n";
				cout << "Please, enter an option: ";
				string dietOption, dietName;
				cin >> dietOption;
				if (isdigit(dietOption[0]) != 0) {
					dietName = getName_fromTable(buildingName + "DietTable", "dietName", "dietID", dietOption);

				listaDasCategorias:
					//display building category table
					cout << "* Select a category \n";
					//listing the categories in the CategoryTableName
					if (tableExists(dietName + buildingName + "CategoryTable") == true)
						listarCoisas("categoryID", "categoryName", dietName + buildingName + "CategoryTable");
					else cout << "* No category!\n";

					cout << "b- Back\n";
					cout << "Please, enter an option: ";
					string categoryOption;
					cin >> categoryOption;

					if (isdigit(categoryOption[0]) != 0) {
					listaDosItems:
						string categoryName;
						//Setting categoryName
						categoryName = getName_fromTable(dietName + buildingName + "CategoryTable", "categoryName", "categoryID", categoryOption);

						//take out all spaces and lower-case all letters
						categoryName = formatName(categoryName);

						//DISPLAY ITEMS AND THEIR PRICES
						cout << "* Prices for " + getName_fromTable(dietName + buildingName + "CategoryTable", "categoryName", "categoryID", categoryOption) + "\n"; //Didnt put string categoryName here cuz it is already formated
						//listing categoryName table selected with prices
						int theID;
						string theName;
						double theprice;
						string queryListarIDnamePrice = "SELECT itemID, itemName, price FROM " + dietName + categoryName + buildingName + "ItemsTable";
						const char* qListarIDnamePrice = queryListarIDnamePrice.c_str();
						qstatepricesManagement = mysql_query(conn, qListarIDnamePrice);
						if (!qstatepricesManagement) {
							res = mysql_store_result(conn);
							while (row = mysql_fetch_row(res)) {
								theID = stoi(row[0]);
								theName = row[1];
								theprice = stod(row[2]);
								cout << theID << "- " << theName << ": $" << theprice << "\n\n";
							}
						}
						else cout << "Query failed: " << mysql_error(conn) << "\n";

						cout << "u- Update price of an item\n";
						cout << "b- Back to categories\n";
						cout << "Please, enter an option: ";
						string itemOption;
						cin >> itemOption;

						if (itemOption == "u") {
							//update price of item
							cout << "* Select item to update price\n";
							//listing categoryName table selected with prices
							int theID;
							string theName;
							double theprice;
							string queryListarIDnamePrice = "SELECT itemID, itemName, price FROM " + dietName + categoryName + buildingName + "ItemsTable";
							const char* qListarIDnamePrice = queryListarIDnamePrice.c_str();
							qstatepricesManagement = mysql_query(conn, qListarIDnamePrice);
							if (!qstatepricesManagement) {
								res = mysql_store_result(conn);
								while (row = mysql_fetch_row(res)) {
									theID = stoi(row[0]);
									theName = row[1];
									theprice = stod(row[2]);
									cout << theID << "- " << theName << ": $" << theprice << "\n";
								}
							}
							else cout << "Query failed: " << mysql_error(conn) << "\n";

							cout << "Please, enter an option: ";
							int itemChosen;
							cin >> itemChosen;
							string itemChosenString = to_string(itemChosen), itemChosenName;
							itemChosenName = getName_fromTable(dietName + categoryName + buildingName + "ItemsTable", "itemName", "itemID", itemChosenString);

							cout << "Price: ";
							double newprice;
							cin >> newprice;
							string newpriceString = to_string(newprice);
							string queryPriceUpdate = "UPDATE " + dietName + categoryName + buildingName + "ItemsTable SET price = " + newpriceString + "WHERE itemName = '" + itemChosenName + "'";
							const char* qPriceUpdate = queryPriceUpdate.c_str();
							qstatepricesManagement = mysql_query(conn, qPriceUpdate);
							if (qstatepricesManagement)
								cout << "Query failed: " << mysql_error(conn) << "\n";

							goto listaDosItems;
						}
						else if (itemOption == "b")
							goto listaDasCategorias;
					}
					else if (categoryOption == "b")
						goto theDiets;
				}
				else if (dietOption == "b")
					goto theMeals;
			}
		}
		else if (escolha == "e")
			goto pricesManagementEnd;
	}
	else puts("Connection to DataBase has failed");

pricesManagementEnd:
	cout << "";
}