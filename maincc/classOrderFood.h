#pragma once
#include<bits/stdc++.h>
using namespace std;

//***class OrderFood***
class OrderFood {
	private:
		int selectedPlace, the_food, the_drink, the_sides, otherFood, paymentMethod;
		double foodOrderTotal;

	public:
		OrderFood() {
			selectedPlace = this->selectedPlace;
			the_food = this->the_food;
			the_drink = this->the_drink;
			the_sides = this->the_sides;
			otherFood = this->otherFood;
			paymentMethod = this->paymentMethod;
			foodOrderTotal = this->foodOrderTotal;
		}

		int get_selectedPlace() {
			return selectedPlace;
		}

		int get_the_food() {
			return the_food;
		}

		int get_the_drink() {
			return the_drink;
		}

		int get_the_sides() {
			return the_sides;
		}

		int get_otherFood() {
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