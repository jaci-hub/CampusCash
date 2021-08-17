#pragma once
#include <iostream>
#include <string>
#include "feesManagement.h"
using namespace std;

double amount_toSend;

double get_transactionFee() { 
    return .02 * amount_toSend;
}