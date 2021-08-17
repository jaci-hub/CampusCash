#pragma once
#include <iostream>
#include <string>
#include <tuple>
using namespace std;



tuple<double, double, double> feesManagement() {
	//display onCampusOrder fee

	//display offCampusOrder fee

	cout << "* Select an option\n";
	cout << "1- Transaction fee\n";
	cout << "2- Delivery fee\n";
	cout << "Please, enter an option: ";
	string feeOption;
	cin >> feeOption;

	if (feeOption == "1") {
		cout << "**Transaction fee: " << "\n\n";
		cout << "1- Update\n";
		cout << "b- Back\n";
	}

	else if (feeOption == "2") {
		cout << "**ON campus Delivery fee: " << "\n\n";
		cout << "**OFF campus Delivery fee: " << "\n\n";
		cout << "1- Update ON campus Delivery fee\n";
		cout << "2- Update OFF campus Delivery fee\n";
		cout << "b- Back\n";
	}

	else feesManagement();

	return make_tuple(1,2,3);
}