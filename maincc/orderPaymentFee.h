#pragma once
#include <iostream>
#include <string>
#include "criar_orderFood.h"
#include "delivery.h"
#include "feesManagement.h"
using namespace std;

double orderPaymentFee() {
    if(on_off==1)
        return .05 * order1.get_foodOrderTotal(); 

    else return .1 * order1.get_foodOrderTotal(); 
}