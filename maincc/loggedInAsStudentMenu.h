#pragma once
#include <iostream>
#include <string>
using namespace std;

//***Opcoes do menu***
unsigned int option;
void menu() {
    cout << "1- Order food" << "\n";
    cout << "2- Send coyote cash" << "\n";
    cout << "3- Log out" << "\n";
    cout << "Please, enter an option: ";
    cin >> option;
    if (option < 1 || option > 3) {
        //system("clear");
        menu();
    }
}
//*******