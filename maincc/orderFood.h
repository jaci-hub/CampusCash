#pragma once
#include <iostream>
#include <string>
#include "classOrderFood.h"
#include "delivery.h"
#include "loggedInAsStudentMenu.h"
#include "listarCoisas.h"
#include "formatName.h"
#include "getName_fromTable.h"
#include "getCurrentDay.h"
#include "getCurrentMonth.h"
#include "getCurrentYear.h"
using namespace std;

int qstateOrderFood;

void order_food() {
    //Stablishing the connection to mysql database
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

    if (conn) {
		foodBuildingsList:
		cout << "* Select a building \n";
		//listing the buildings in the foodBuildingsTable
		if (tableExists("foodBuildingsTable") == true)
			listarCoisas("foodBuildingID", "foodBuildingName", "foodBuildingsTable");
		else cout << "* No building!\n";

		cout << "e- EXIT\n";
		cout << "Please, enter an option: ";
		string optionEscolhida;
		cin >> optionEscolhida;
		if (isdigit(optionEscolhida[0]) != 0) {
			//Setting buildingName
			myOrder.selectedBuilding = getName_fromTable("foodBuildingsTable", "foodBuildingName", "foodBuildingID", optionEscolhida);
			//take out all spaces and lower-case all letters
			myOrder.selectedBuilding = formatName(myOrder.selectedBuilding);

            DietsList:
            string dietOption;
            cout << "* Select a diet\n";
            //listar as diets from myOrder.selectedBuilding + "DietTable"
            if (tableExists(myOrder.selectedBuilding + "DietTable") == true)
                listarCoisas("dietID", "dietName", myOrder.selectedBuilding + "DietTable");
            else cout << "* No diet!\n";

            cout << "b- Back\n";
            cout << "Please, enter an option: ";
            cin >> dietOption;
            if (isdigit(dietOption[0]) != 0) {
                MealsList:
                myOrder.selectedDiet = getName_fromTable(myOrder.selectedBuilding + "DietTable", "dietName", "dietID", dietOption);
                myOrder.selectedDiet = formatName(myOrder.selectedDiet);

                //Display menu
                string dayToday = "31" /*getCurrentDay()*/, mes = getCurrentMonth(), ano = getCurrentYear();
                string menuTable = myOrder.get_selectedDiet() + myOrder.get_selectedBuilding() + "MenuPlanTable" + mes + ano;
                string timesAndPriceTableName = myOrder.get_selectedBuilding() + "MealsTimeAndPrice";
                string mealID, mealName, dishAndIngredients, price, startTime, endTime;
                string querySelectAllSix = "SELECT " + menuTable + ".mealID, " + menuTable + ".meal, " + menuTable + ".Day" + dayToday + ", " + timesAndPriceTableName + ".price, " + timesAndPriceTableName + ".startTime, " + timesAndPriceTableName + ".endTime FROM " + menuTable + " INNER JOIN " + timesAndPriceTableName + " ON " + menuTable + ".mealID = " + timesAndPriceTableName + ".mealID";
                const char* qSelectAllSix = querySelectAllSix.c_str();
                qstateOrderFood = mysql_query(conn, qSelectAllSix);
                if (!qstateOrderFood) {
                    res = mysql_store_result(conn);
                    while (row = mysql_fetch_row(res)) {
                        mealID = row[0];
                        mealName = row[1];
                        dishAndIngredients = row[2];
                        price = row[3];
                        startTime = row[4];
                        endTime = row[5];

                        //only display if there is dish-ingredients
                        if (dishAndIngredients != "none") {
                            cout << mealID << "- " << mealName << ": $" << price << "\n";
                            cout << startTime << " - " << endTime << "\n";
                            cout << dishAndIngredients << "\n";
                        }
                    }
                }
                else cout << "Query failed: " << mysql_error(conn) << "\n";

                cout << "5- Other\n";
                cout << "b- Back\n";
                cout << "Please, enter an option: ";
                string mealSelecionado;
                cin >> mealSelecionado;
                myOrder.foodOrderTotal = 0; //reset it every time the user wants to order more!
                string categoryOption0, categoryOption1, categoryOption2;
                if (mealSelecionado == "b")
                    goto DietsList;
                else if (mealSelecionado == "5") {
                    myOrder.selectedMeal = "Other";

                categoryListInitial:
                    //listar categorias 0th time
                    string CategoryTableName = myOrder.get_selectedDiet() + myOrder.get_selectedBuilding() + "CategoryTable";
                    cout << "* Select a category \n";
                    if (tableExists(CategoryTableName)) {
                        int theID;
                        string theName;
                        string queryListarIDname = "SELECT categoryID, categoryName FROM " + CategoryTableName;
                        const char* qListarIDname = queryListarIDname.c_str();
                        qstateOrderFood = mysql_query(conn, qListarIDname);
                        if (!qstateOrderFood) {
                            res = mysql_store_result(conn);
                            while (row = mysql_fetch_row(res)) {
                                theID = stoi(row[0]);
                                theName = row[1];
                                cout << theID << "- " << theName << "\n";
                            }
                        }
                        else cout << "Query failed: " << mysql_error(conn) << "\n";
                    }
                    else cout << "* No category!\n";
                    cout << "n- None\n";
                    cout << "b- Back\n";
                    cout << "Please, enter an option: ";
                    cin >> categoryOption0;
                    if (isdigit(categoryOption0[0]) != 0) {
                        //listar os items na selected category
                        string categoryName = getName_fromTable(CategoryTableName, "categoryName", "categoryID", categoryOption0);

                        //take out all spaces and lower-case all letters
                        categoryName = formatName(categoryName);

                        //naming the items table
                        string ItemsTableName = categoryName + myOrder.get_selectedDiet() + myOrder.get_selectedBuilding() + "ItemsTable";
                        cout << "* All " + getName_fromTable(CategoryTableName, "categoryName", "categoryID", categoryOption0) + "\n";
                        if (tableExists(ItemsTableName) == true) {
                            //listing categoryName table selected
                            listarCoisas("itemID", "itemName", ItemsTableName);
                        }
                        else cout << "* No " << getName_fromTable(CategoryTableName, "categoryName", "categoryID", categoryOption0) << "!\n";
                        cout << "b- Back\n";
                        cout << "Please, enter an option: ";
                        string itemOption;
                        cin >> itemOption;
                        if (isdigit(itemOption[0]) != 0) {
                            myOrder.selectedSideOne = getName_fromTable(ItemsTableName, "itemName", "itemID", itemOption);
                            myOrder.foodOrderTotal += stod(getName_fromTable(ItemsTableName, "price", "itemID", itemOption));
                        }
                        else if (itemOption == "b")
                            goto categoryListInitial;
                    }
                    else if (categoryOption0 == "n")
                        goto deliveryPart;
                    else if (categoryOption0 == "b")
                        goto MealsList;

                    goto categoryList;
                }
                else if (isdigit(mealSelecionado[0]) != 0) {
                    myOrder.selectedMeal = getName_fromTable(menuTable, "meal", "mealID", mealSelecionado);
                    //setting the price of the meal
                    myOrder.foodOrderTotal += stod(getName_fromTable(myOrder.get_selectedBuilding() + "MealsTimeAndPrice", "price", "mealID", mealSelecionado));
                    categoryList:
                    //listar categorias 1st time
                    string CategoryTableName = myOrder.get_selectedDiet() + myOrder.get_selectedBuilding() + "CategoryTable";
                    cout << "* Select a category \n";
                    if (tableExists(CategoryTableName)) {
                        //listing the categories in the CategoryTableName
                        int theID;
                        string theName;
                        string queryListarIDname = "SELECT categoryID, categoryName FROM " + CategoryTableName;
                        const char* qListarIDname = queryListarIDname.c_str();
                        qstateOrderFood = mysql_query(conn, qListarIDname);
                        if (!qstateOrderFood) {
                            res = mysql_store_result(conn);
                            while (row = mysql_fetch_row(res)) {
                                theID = stoi(row[0]);
                                theName = row[1];
                                if (to_string(theID) != categoryOption0) //without the previously selected!
                                    cout << theID << "- " << theName << "\n";
                            }
                        }
                        else cout << "Query failed: " << mysql_error(conn) << "\n";
                    }
                    else cout << "* No category!\n";
                    cout << "n- None\n";
                    cout << "b- Back\n";
                    cout << "Please, enter an option: ";
                    cin >> categoryOption1;
                    if (isdigit(categoryOption1[0]) != 0) {
                        //listar os items na selected category
                        string categoryName = getName_fromTable(CategoryTableName, "categoryName", "categoryID", categoryOption1);

                        //take out all spaces and lower-case all letters
                        categoryName = formatName(categoryName);

                        //naming the items table
                        string ItemsTableName = categoryName + myOrder.get_selectedDiet() + myOrder.get_selectedBuilding() + "ItemsTable";
                        cout << "* All " + getName_fromTable(CategoryTableName, "categoryName", "categoryID", categoryOption1) + "\n";
                        if (tableExists(ItemsTableName) == true) {
                            //listing categoryName table selected
                            listarCoisas("itemID", "itemName", ItemsTableName);
                        }
                        else cout << "* No " << getName_fromTable(CategoryTableName, "categoryName", "categoryID", categoryOption1) << "!\n";
                        cout << "b- Back\n";
                        cout << "Please, enter an option: ";
                        string itemOption;
                        cin >> itemOption;
                        if (isdigit(itemOption[0]) != 0) {
                            myOrder.selectedSideTwo = getName_fromTable(ItemsTableName, "itemName", "itemID", itemOption);
                            myOrder.foodOrderTotal += stod(getName_fromTable(ItemsTableName, "price", "itemID", itemOption));
                        }
                        else if (itemOption == "b")
                            goto categoryList;

                        categoryListReduced:
                        //listar categorias 2nd time (without the previously selected)
                        cout << "* Select a category \n";
                        int theID;
                        string theName;
                        string queryListarIDname = "SELECT categoryID, categoryName FROM " + CategoryTableName;
                        const char* qListarIDname = queryListarIDname.c_str();
                        qstateOrderFood = mysql_query(conn, qListarIDname);
                        if (!qstateOrderFood) {
                            res = mysql_store_result(conn);
                            while (row = mysql_fetch_row(res)) {
                                theID = stoi(row[0]);
                                theName = row[1];
                                if(to_string(theID) != categoryOption1 && to_string(theID) != categoryOption0) //without the previously selected!
                                    cout << theID << "- " << theName << "\n";
                            }
                        }
                        else cout << "Query failed: " << mysql_error(conn) << "\n";
                        cout << "n- None\n";
                        cout << "b- Back\n";
                        cout << "Please, enter an option: ";
                        cin >> categoryOption2;
                        if (isdigit(categoryOption2[0]) != 0) {
                            //listar os items na selected category
                            string categoryName = getName_fromTable(CategoryTableName, "categoryName", "categoryID", categoryOption2);

                            //take out all spaces and lower-case all letters
                            categoryName = formatName(categoryName);

                            //naming the items table
                            string ItemsTableName = categoryName + myOrder.get_selectedDiet() + myOrder.get_selectedBuilding() + "ItemsTable";
                            cout << "* All " + getName_fromTable(CategoryTableName, "categoryName", "categoryID", categoryOption2) + "\n";
                            if (tableExists(ItemsTableName) == true) {
                                //listing categoryName table selected
                                listarCoisas("itemID", "itemName", ItemsTableName);
                            }
                            else cout << "* No " << getName_fromTable(CategoryTableName, "categoryName", "categoryID", categoryOption2) << "!\n";
                            cout << "b- Back\n";
                            cout << "Please, enter an option: ";
                            string itemOption;
                            cin >> itemOption;
                            if (isdigit(itemOption[0]) != 0) {
                                myOrder.selectedSideThree = getName_fromTable(ItemsTableName, "itemName", "itemID", itemOption);
                                myOrder.foodOrderTotal += stod(getName_fromTable(ItemsTableName, "price", "itemID", itemOption));
                            }
                            else if (itemOption == "b")
                                goto categoryListReduced;
                        }
                        else if (categoryOption2 == "n")
                            goto deliveryPart;
                        else if (categoryOption2 == "b")
                            goto categoryList;
                    }
                    else if (categoryOption1 == "n")
                        goto deliveryPart;
                    else if (categoryOption1 == "b")
                        goto MealsList;
                }
                
            deliveryPart:
                delivery();
            }
            else if (dietOption == "b")
                goto foodBuildingsList;
		}
		else if (optionEscolhida == "e")
			goto order_foodEnd;
    }
    else puts("Connection to DataBase has failed");

order_foodEnd:
	cout << "";
}