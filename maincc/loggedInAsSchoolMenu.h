#pragma once
#include <iostream>
#include <string>
using namespace std;

//***Opcoes do menu***
unsigned int menuChoice;
void schoolOptionMenu() {
    cout << "1- Show Orders\n";
    cout << "2- Management\n";
    cout << "3- Log Out\n";
    cout << "Please, enter an option: ";
    cin >> menuChoice;

    if (menuChoice < 1 || menuChoice > 3) {
        //system("clear");
        schoolOptionMenu();
    }
}
//*******