#pragma once
#include<bits/stdc++.h>
using namespace std;

//THIS APP CAN EVEN BE AN ALTERNATIVE WAY FOR STUDENTS TO REGISTER FOR THE TYPE OF MEAL PLAN THEY WANT FOR A PARTICULAR YEAR/SEMESTER

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