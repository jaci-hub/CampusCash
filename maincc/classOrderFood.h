#pragma once
#include <iostream>
#include <string>
using namespace std;

//***class OrderFood***
class OrderFood {
private:
	//food
	string selectedBuilding, selectedDiet, selectedMeal, selectedSideOne, selectedSideTwo, selectedSideThree;
	//delivery
	string selectedOnOffCampus, selectedDorm, selectedRoom;
	//total
	double foodOrderTotal;

public:
	OrderFood() {
		//food
		selectedBuilding = this->selectedBuilding;
		selectedDiet = this->selectedDiet;
		selectedMeal = this->selectedMeal;
		selectedSideOne = this->selectedSideOne;
		selectedSideTwo = this->selectedSideTwo;
		selectedSideThree = this->selectedSideThree;
		//delivery
		selectedOnOffCampus = this->selectedOnOffCampus;
		selectedDorm = this->selectedDorm;
		selectedRoom = this->selectedRoom;
		//total
		foodOrderTotal = this->foodOrderTotal;
	}
	//food
	string get_selectedBuilding() {
		return selectedBuilding;
	}

	string get_selectedDiet() {
		return selectedDiet;
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
	
	//delivery
	string get_selectedOnOffCampus() {
		return selectedOnOffCampus;
	}

	string get_selectedDorm() {
		return selectedDorm;
	}

	string get_selectedRoom() {
		return selectedRoom;
	}

	//total
	double get_foodOrderTotal() {
		return foodOrderTotal;
	}

	friend void order_food();
	friend void delivery();
	friend void orderFood_payment();
};

OrderFood myOrder; //criacao da myOrder type OrderFood
//*******