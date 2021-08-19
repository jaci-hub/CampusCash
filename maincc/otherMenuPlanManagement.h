#pragma once
#include <iostream>
#include <string>
#include "dropTable.h"
using namespace std;

string CategoryTableName, ItemsTableName;

int qstateOtherMenuPlanManagement;

void otherMenuPlanManagement() {
	//Stablishing the connection to mysql database
	MYSQL* conn;
	//MYSQL_ROW row;
	//MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

	if (conn) {
	listaDasCategories:
		//criar CategoryTableName if it doesnt exist yet
		CategoryTableName = allinOne_class.get_buildingName() + "CategoryTable";

		if (tableExists(CategoryTableName) == false) {
			string queryOtherCategoryTable = "CREATE TABLE " + CategoryTableName + "(categoryID INT KEY AUTO_INCREMENT, categoryName VARCHAR(255) UNIQUE) ";
			const char* qOtherCategoryTable = queryOtherCategoryTable.c_str();
			qstateOtherMenuPlanManagement = mysql_query(conn, qOtherCategoryTable);
			if (qstateOtherMenuPlanManagement)
				cout << "Query failed: " << mysql_error(conn) << "\n";

			//Add CategoryTableName to the MCIrecordTable
			addCoisaToTable(CategoryTableName, "CategoryTables", "MCIrecordTable"); //ADDED
		}
		
		cout << "* Select a category \n";
		if (tableExists(CategoryTableName)) {
			//listing the categories in the CategoryTableName
			listarCoisas("categoryID", "categoryName", CategoryTableName);
		}
		else cout << "No categories!\n";

		//adding/removing a category options
		cout << "a- Add\n";
		cout << "r- Remove\n";
		cout << "e- EXIT other\n";
		cout << "Please, enter an option: ";
		string categoryOption;
		cin >> categoryOption;

		//heading to Items table
		if (isdigit(categoryOption[0]) != 0) {
			listaDosItems:
			string categoryName;
			//Setting categoryName
			categoryName = getName_fromTable(CategoryTableName, "categoryName", "categoryID", categoryOption);

			//take out all spaces and lower-case all letters
			categoryName = formatName(categoryName);
			ItemsTableName = categoryName + allinOne_class.get_buildingName() + "ItemsTable";

			cout << "* All " + getName_fromTable(CategoryTableName, "categoryName", "categoryID", categoryOption) + "\n";
			if (tableExists(ItemsTableName)==true) {
				//listing categoryName table selected
				listarCoisas("itemID", "itemName", categoryName + allinOne_class.get_buildingName() + "ItemsTable");
			}
			else cout << "No " << getName_fromTable(CategoryTableName, "categoryName", "categoryID", categoryOption) << "!\n";

			//adding/removing an item options
			cout << "a- Add\n";
			cout << "r- Remove\n";
			cout << "b- Back to categories\n";
			cout << "Please, enter an option: "; //CANT SELECT ITEMS!!! THEY ARE ONLY TO BE DISPLAYED!!!
			string itemOption;
			cin >> itemOption;

			//add item
			if (itemOption == "a") { 
				//***create Itemstable for categoryname if it doesnt exist yet
				//take out all spaces and lower-case all letters
				categoryName = formatName(categoryName);

				if (tableExists(ItemsTableName) == false) {
					string queryNewItemsTable = "CREATE TABLE " + ItemsTableName + "(itemID INT KEY AUTO_INCREMENT, itemName VARCHAR(255) UNIQUE, price DOUBLE(5,2))";
					const char* qNewItemsTable = queryNewItemsTable.c_str();
					qstateOtherMenuPlanManagement = mysql_query(conn, qNewItemsTable);
					if (qstateOtherMenuPlanManagement)
						cout << "Query failed: " << mysql_error(conn) << "\n";

					//Add ItemsTableName to the MCIrecordTable
					addCoisaToTable(ItemsTableName, "ItemsTables", "MCIrecordTable"); //ADDED
				} 

				cout << "* Name: ";
				string newItemName;
				cin.ignore();
				getline(cin, newItemName);
				addCoisaToTable(newItemName, "itemName", categoryName + allinOne_class.get_buildingName() + "ItemsTable"); //ADDED
				
				cout << "* Price($): ";
				double price;
				cin >> price;
				string priceString=to_string(price);
				string queryAdd = "INSERT INTO " + categoryName + allinOne_class.get_buildingName() + "ItemsTable(price) VALUE(" + priceString + ")";
				const char* qAdd = queryAdd.c_str();
				qstateAdd = mysql_query(conn, qAdd);
				if (qstateAdd)
					cout << "Query failed: " << mysql_error(conn) << "\n";

				goto listaDosItems;
			}
			
			//remove item
			else if (itemOption == "r") {
				cout << "* Select item to be removed\n";
				//listing items from itemsTable
				listarCoisas("itemID", "itemName", categoryName + allinOne_class.get_buildingName() + "ItemsTable");

				cout << "Please, enter an option: ";
				int IDtobeRem;
				cin >> IDtobeRem;
				string ItemTobeRem, IDtobeRemString = to_string(IDtobeRem);

				//Getting the item name first
				ItemTobeRem = getName_fromTable(categoryName + allinOne_class.get_buildingName() + "ItemsTable", "itemName", "itemID", IDtobeRemString);

				//Now removing the item
				removeCoisaFromTable(ItemTobeRem, "itemName", categoryName + allinOne_class.get_buildingName() + "ItemsTable"); //REMOVED
			
				goto listaDosItems;
			}

			else if (itemOption == "b")
				goto listaDasCategories;
		}

		//add category
		else if (categoryOption == "a") {
			cout << "* Name: ";
			string newCategoryName;
			cin.ignore();
			getline(cin, newCategoryName);
			addCoisaToTable(newCategoryName, "categoryName", CategoryTableName); //ADDED

			goto listaDasCategories;
		}

		//remove category
		else if (categoryOption == "r") {
			cout << "* Select category to be removed\n";
			//listing the categories in the CategoryTableName
			listarCoisas("categoryID", "categoryName", CategoryTableName);

			cout << "Please, enter an option: ";
			int IDtobeRem;
			cin >> IDtobeRem;
			string categoryTobeRem, IDtobeRemString = to_string(IDtobeRem);

			//Getting the categoryName name first
			categoryTobeRem = getName_fromTable(CategoryTableName, "categoryName", "categoryID", IDtobeRemString);

			//Now removing the category
			removeCoisaFromTable(categoryTobeRem, "categoryName", CategoryTableName); //REMOVED

				//***dropping the category itemsTable***//
			//take out all spaces and lower-case all letters
			categoryTobeRem = formatName(categoryTobeRem);

			dropTable(categoryTobeRem + allinOne_class.get_buildingName() + "ItemsTable"); //TABLE DROPPED

			//Remove ItemsTableName from the MCIrecordTable
			removeCoisaFromTable(ItemsTableName, "ItemsTables", "MCIrecordTable"); //ADDED

			goto listaDasCategories;
		}

		//end funcao
		else if (categoryOption == "e")
			goto otherMenuPlanManagementEnd;
	}
	else puts("Connection to DataBase has failed");

otherMenuPlanManagementEnd:
	cout << "";
}

