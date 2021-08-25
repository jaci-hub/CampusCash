#pragma once
#include <iostream>
#include <string>
#include "file_com_pragmaonce_mysql.h"
#include "classOrderFood.h"
#include "orderTotal.h"
#include "formatName.h"
#include "loggedInAsStudentMenu.h"
#include "getName_fromTable.h"
#include "listarCoisas.h"
using namespace std;

void order_food() {
	selectPlace:
	cout << "*** Order from \n";
	//listing the buildings in the foodBuildingsTable
	if (tableExists("foodBuildingsTable") == true)
		listarCoisas("foodBuildingID", "foodBuildingName", "foodBuildingsTable");
	else cout << "* No building!\n";
	cout << "b-Back\n";
	cout << "Please, enter an option: ";
	string buildingChoice;
	cin >> buildingChoice;
	//heading to diets
	if (isdigit(buildingChoice[0]) != 0) {
		//Setting buildingName
		order1.selectedPlace = getName_fromTable("foodBuildingsTable", "foodBuildingName", "foodBuildingID", buildingChoice);
		//take out all spaces and lower-case all letters
		order1.selectedPlace = formatName(order1.selectedPlace);

		selectDiet:
		cout << "*** Select diet \n";
		//listar diets

		cout << "b-Back\n";
		cout << "Please, enter an option: ";
		string dietChoice;
		cin >> dietChoice;
		if (isdigit(dietChoice[0]) != 0) {
			order1.selectedDiet = getName_fromTable();
			//formatName??

		selectMeal:
			//Getting the meal
			if (order1.selectedPlace == 2) {
				cout << "*** What would you like to order today? \n";
				//list meals

				cout << "b-Back\n";
				cout << "Please, enter an option: ";
				cin >> order1.the_meal;

			selectPaymentMethod:
				// 	ASK IF STUDENT WANTS TO PAY WITH mealPlanBalance OR Coyote Cash
				cout << "**Pay with: \n";
				cout << "1- Meals\n";
				cout << "2- Coyote Cash\n";
				cout << "Please, enter an option: ";
				cin >> order1.paymentMethod;

				order_total();
		}
		else if (dietChoice == "b")
			goto selectPlace;
	}

	else if (buildingChoice == "b")
		goto order_foodEnd;

order_foodEnd:
	cout << "";
}