#pragma once
#include <iostream>
#include <string>
#include "classOrderFood.h"
#include "delivery.h"
#include "orderTotal.h"
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
                myOrder.selectedDiet = getName_fromTable(myOrder.selectedBuilding + "DietTable", "dietName", "dietID", dietOption);
                myOrder.selectedDiet = formatName(myOrder.selectedDiet);

                //Display menu
                string dayToday = "30" /*getCurrentDay()*/, mes = getCurrentMonth(), ano = getCurrentYear();
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
                            cout << dishAndIngredients << "\n\n";
                        }
                    }
                }
                else cout << "Query failed: " << mysql_error(conn) << "\n";

                cout << "5- Other\n";
                cout << "b- Back\n";
                cout << "Please, enter an option: ";
                string mealSelecionado;
                cin >> mealSelecionado;

                if (mealSelecionado == "b")
                    goto DietsList;
                else if (isdigit(mealSelecionado[0]) != 0) {
                    //listar categorias 2x
                }
                else if (mealSelecionado == "5") {
                    //listar categorias 3x
                }
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