#pragma once
#include <iostream>
#include <string>
#include "classOrderFood.h"
#include "criar_orderFood.h"

void order_total() {
	//Cafe
	if (order1.the_food == 0 && order1.selectedPlace == 1)
		order1.foodOrderTotal = 5.90;
	
	else if (order1.the_food == 1 && order1.selectedPlace == 1)
		order1.foodOrderTotal = 6.90;

	else if (order1.the_food == 2 && order1.selectedPlace == 1)
		order1.foodOrderTotal = 7.90;

	else if (order1.the_food == 3 && order1.selectedPlace == 1)
		order1.foodOrderTotal = 8.90;

	//McCain
	else if (order1.the_food == 1 && order1.selectedPlace == 2)
		order1.foodOrderTotal = 5.40;

	else if (order1.the_food == 2 && order1.selectedPlace == 2)
		order1.foodOrderTotal = 7.40;

	else if (order1.the_food == 3 && order1.selectedPlace == 2)
		order1.foodOrderTotal = 8.40;
}