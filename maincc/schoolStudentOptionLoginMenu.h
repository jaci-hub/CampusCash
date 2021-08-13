#pragma once
#include <iostream>
#include <string>
using namespace std;

//THIS APP CAN EVEN BE AN ALTERNATIVE WAY FOR STUDENTS TO REGISTER FOR THE TYPE OF MEAL PLAN THEY WANT FOR A PARTICULAR YEAR/SEMESTER

//***Opcoes do menu***
unsigned int menuChoice;
void schoolOptionMenu() {
    cout << "1- Show Orders by Buildings\n";
    cout << "2- Cash Transaction Records\n";
    cout << "3- Management\n";
    cout << "4- Log Out\n";
    cout << "Please, enter an option: ";
    cin >> menuChoice;

    if (menuChoice < 1 || menuChoice > 4) {
        //system("clear");
        schoolOptionMenu();
    }
}
//*******