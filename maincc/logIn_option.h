#pragma once
#include<bits/stdc++.h>
using namespace std;

//THIS APP CAN EVEN BE AN ALTERNATIVE WAY FOR STUDENTS TO REGISTER FOR THE TYPE OF MEAL PLAN THEY WANT FOR A PARTICULAR YEAR/SEMESTER

//*** log in option ***
unsigned int selection;
void logIn_option() {
    cout << "Log In as:\n";
    cout << "1- School" << "\n";
    cout << "2- Student" << "\n";
    cout << "3- EXIT" << "\n";
    cout << "Please, enter an option: ";
    cin >> selection;
    if (selection < 1 || selection>3) {
        //system("clear");
        logIn_option();
    }
}
//*******