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
using namespace std;

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