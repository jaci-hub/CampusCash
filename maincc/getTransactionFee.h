#pragma once

double amount_toSend;

double get_transactionFee() { //charge a 2% fee in every transaction
    return .02 * amount_toSend;
}