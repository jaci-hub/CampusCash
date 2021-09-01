#pragma once
#include <iostream>
#include <string>
using namespace std;

//***class Sender***
class Sender {
private:
    double balance;
    string name, email, id; //left id as string and not int cuz it can have leading zeros
     int mealPlanBalance;

public:
    Sender() {
        balance = this->balance;
        name = this->name;
        email = this->email;
        id = this->id;
        mealPlanBalance = this->mealPlanBalance;
    }

    double get_balance() {
        return balance;
    }

    int get_mealPlanBalance() {
        return mealPlanBalance;
    }

    string get_name() {
        return name;
    }

    string get_email() {
        return email;
    }

    string get_id() {
        return id;
    }

    friend void criar_sender(); //so it can access the private name, so it is set in criar_sender()
    friend void send_cash(); //so it can access the private balance, so it is updated when transaction is made!
    friend void orderFood_payment(); //so it can access the private balance, so it is updated when order is made!
    //friend void show_orders_byFoodBuilding();
};

Sender student1; //criacao do studante1 type Sender
//*******