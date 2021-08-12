#pragma once
#include<bits/stdc++.h>
#include "diningManagement.h"
using namespace std;

int managementPIN, managementOption;

void management() {
	//Ask for PIN cuz only limited staff can log in
	cout << "PIN: ";
	cin >> managementPIN;
	if (managementPIN == 1234 || optionFinalmente == "4") {
		cout << "0- Meals time period\n";
		cout << "1- Dining\n";
		cout << "2- Delivery\n";
		cout << "3- Prices\n";
		cout << "4- Fees\n";
		cout << "5- Back to Menu\n";
		cout << "Please, enter an option: ";
		cin >> managementOption;

		//Meals time period
		if (managementOption == 0) {
			//mealsTimePeriodManagement();
		}

		//Dining
		if (managementOption == 1) {
			diningManagement(); //DONE!!!
		}

		//Delivery
		else if (managementOption == 2) {
			//deliveryManagement();
		}

		//Pricesss
		else if (managementOption == 3) {
			//pricesManagement();
		}

		//Fees
		else if (managementOption == 4) {
			//feesManagement();
		}
	}
	else { 
		cout << "Invalid PIN\n";
		management(); 
	}
}