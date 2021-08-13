#pragma once
#include <iostream>
#include <string>
#include "criar_orderFood.h"
#include "delivery.h"

double orderPaymentFee() {
    if(on_off==1)
        return .05 * order1.get_foodOrderTotal(); //charge 5% if delivering ON campus

    else return .1 * order1.get_foodOrderTotal(); //charge 10% if delivering OFF campus [probably should vary with distance!!!]
}