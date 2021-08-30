#pragma once
#include <iostream>
#include <string>
using namespace std;

//***class OrderFood***
class OrderFood {
private:
	string selectedBuilding, selectedMeal, selectedSideOne, selectedSideTwo, selectedSideThree, paymentMethod;
	double foodOrderTotal;

public:
	OrderFood() {
		selectedBuilding = this->selectedBuilding;
		selectedMeal = this->selectedMeal;
		selectedSideOne = this->selectedSideOne;
		selectedSideTwo = this->selectedSideTwo;
		selectedSideThree = this->selectedSideThree;
		paymentMethod = this->paymentMethod;
		foodOrderTotal = this->foodOrderTotal;
	}

	string get_selectedBuilding() {
		return selectedBuilding;
	}

	string get_selectedMeal() {
		return selectedMeal;
	}

	string get_selectedSideOne() {
		return selectedSideOne;
	}

	string get_selectedSideTwo() {
		return selectedSideTwo;
	}

	string get_selectedSideThree() {
		return selectedSideThree;
	}

	double get_foodOrderTotal() {
		return foodOrderTotal;
	}

	friend void order_food();
	friend void order_total();
	friend void orderFood_payment();
};

OrderFood order1; //criacao da order1 type OrderFood
//*******