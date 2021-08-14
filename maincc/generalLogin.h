#pragma once
#include <iostream>
#include <string>
using namespace std;

//*** log in option ***
unsigned int selection;
void generalLogIn() {
    cout << "Log In as:\n";
    cout << "1- School" << "\n";
    cout << "2- Student" << "\n";
    cout << "3- EXIT" << "\n";
    cout << "Please, enter an option: ";
    cin >> selection;
    if (selection < 1 || selection>3) {
        //system("clear");
        generalLogIn();
    }
}
//*******