#pragma once
#include <iostream>
#include <string>
#include "diningManagement.h"
#include "deliveryManagement.h"
#include "feesManagement.h"
#include "timeManagement.h"
#include "pricesManagement.h"
using namespace std;

int managementOption;

void management() {
		cout << "0- Times\n";
		cout << "1- Dining\n";
		cout << "2- Delivery\n";
		cout << "3- Prices\n";
		cout << "4- Fees\n";
		cout << "5- Back to main Menu\n"; //THIS IS IN THE if-statement in main()
		cout << "Please, enter an option: ";
		cin >> managementOption;

		//Meals time period
		if (managementOption == 0) {
			timeManagement();
		}

		//Dining
		if (managementOption == 1) {
			diningManagement();
		}

		//Delivery
		else if (managementOption == 2) {
			deliveryManagement();
		}

		//Prices
		else if (managementOption == 3) {
			pricesManagement();
		}

		//Fees
		else if (managementOption == 4) {
			feesManagement();
		}
}