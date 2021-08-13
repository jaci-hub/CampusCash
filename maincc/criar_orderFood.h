#pragma once
#include <iostream>
#include <string>
#include "classOrderFood.h"
#include "orderTotal.h"
#include "menu.h"
using namespace std;

//Order Food ------------->>WAIT UNTIL management() IS DONE!!!
void order_food() {
	selectPlace:
	cout << "*** Order from \n";
	cout << "1- Simplot Cafe\n";
	cout << "2- McCain\n";
	cout << "Please, enter an option: ";
	cin >> order1.selectedPlace;

	//Cafe Option
	if (order1.selectedPlace == 1) {
		cout << "*** What would you like to order today? \n";
		cout << "0- None\n";
		cout << "1- Breakfast\n";
		cout << "2- Brunch \n";
		cout << "3- Lunch\n";
		cout << "4- Dinner\n";
		cout << "Please, enter an option: ";
		cin >> order1.the_food;
		//Getting Drinks
		if (order1.the_food >= 0 && order1.the_food <= 4) {
			cout << "*** Drinks?\n";
			cout << "0- None\n";
			cout << "1- Coke \n";
			cout << "2- Mountain Dew\n";
			cout << "3- Sprite\n";
			cout << "Please, enter an option: ";
			cin >> order1.the_drink;
			//Getting Sides
			if (order1.the_drink >= 0 && order1.the_drink <= 3) {
				cout << "*** Sides?\n";
				cout << "0- None\n";
				cout << "1- Fruit \n";
				cout << "2- Brownnie\n";
				cout << "3- Cake\n";
				cout << "Please, enter an option: ";
				cin >> order1.the_sides;
			}
			//Getting other Food
			if (order1.the_sides >= 0 && order1.the_sides <= 3) {
				cout << "*** Other Food\n";
				cout << "0- None\n";
				cout << "1- Fruit \n";
				cout << "2- Brownnie\n";
				cout << "3- Cake\n";
				cout << "Please, enter an option: ";
				cin >> order1.otherFood;
			}
		}

		order_total();
	}

	//McCain Option
	//Getting the food
	 else if (order1.selectedPlace == 2) {
		cout << "*** What would you like to order today? \n";
		cout << "0- None\n";
		cout << "1- Burger\n";
		cout << "2- Sandwich\n";
		cout << "3- The Dean\n";
		cout << "Please, enter an option: ";
		cin >> order1.the_food;
		//Getting the drink
		if (order1.the_food >= 0 && order1.the_food <= 3) {
			cout << "*** Drinks?\n";
			cout << "0- None\n";
			cout << "1- Coke \n";
			cout << "2- Mountain Dew\n";
			cout << "3- Sprite\n";
			cout << "Please, enter an option: ";
			cin >> order1.the_drink;
			//Getting the sides
			if (order1.the_drink >= 0 && order1.the_drink <= 3) {
				cout << "*** Sides?\n";
				cout << "0- None\n";
				cout << "1- Fruit \n";
				cout << "2- Brownnie\n";
				cout << "3- Cake\n";
				cout << "Please, enter an option: ";
				cin >> order1.the_sides;
			}
				//Getting other Food
				if (order1.the_sides >= 0 && order1.the_sides <= 3) {
					cout << "*** Other Food\n";
					cout << "0- None\n";
					cout << "1- Fruit \n";
					cout << "2- Brownnie\n";
					cout << "3- Cake\n";
					cout << "Please, enter an option: ";
					cin >> order1.otherFood;
				}
		}

		// 	ASK IF STUDENT WANTS TO PAY WITH mealPlanBalance OR Coyote Cash
		cout << "**Pay with: \n";
		cout << "1- Meals\n";
		cout << "2- Coyote Cash\n";
		cout << "Please, enter an option: ";
		cin >> order1.paymentMethod;

		order_total();
	}

	else {
		//system("clear");
		goto selectPlace;
	}
}