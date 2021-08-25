#pragma once
#include <iostream>
#include <string>
using namespace std;

//***class OrderFood***
class OrderFood {
	private:
		string selectedPlace, selectedDiet, the_meal, the_drink, the_sides, otherFood, paymentMethod;
		double foodOrderTotal;

	public:
		OrderFood() {
			selectedPlace = this->selectedPlace;
			selectedDiet = this->selectedDiet;
			the_meal = this->the_meal;
			the_drink = this->the_drink;
			the_sides = this->the_sides;
			otherFood = this->otherFood;
			paymentMethod = this->paymentMethod;
			foodOrderTotal = this->foodOrderTotal;
		}

		string get_selectedPlace() {
			return selectedPlace;
		}

		string get_the_food() {
			return the_meal;
		}

		string get_the_drink() {
			return the_drink;
		}

		string get_the_sides() {
			return the_sides;
		}

		string get_otherFood() {
			return otherFood;
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