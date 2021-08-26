#pragma once
#include <iostream>
#include <string>
using namespace std;

//THIS APP CAN EVEN BE AN ALTERNATIVE WAY FOR STUDENTS TO REGISTER FOR THE TYPE OF MEAL PLAN THEY WANT FOR A PARTICULAR YEAR/SEMESTER

//***Opcoes de delivery***
int on_off, hall, room;
string offCampusAddress;
void delivery() {
    cout << "*** Where do you want your food delivered?" << "\n";
    cout << "1- ON campus" << "\n";
    cout << "2- OFF campus" << "\n";
    cout << "Please, enter an option: ";
    cin >> on_off;

    //ON campus
    if (on_off == 1) {
        cout << "*** Select hall/apartment" << "\n";
        cout << "1- Anderson" << "\n";
        cout << "2- Hayman" << "\n";
        cout << "3- Vorhees" << "\n";
        cout << "4- Simplot" << "\n";
        cout << "5- Finney" << "\n";
        cout << "6- Mustard" << "\n";
        cout << "7- Ketchup" << "\n";
        cout << "8- Sawtooth" << "\n";
        cout << "9- Owyhee" << "\n";
        cout << "Please, enter an option: ";
        cin >> hall;

        cout << "*** Select room number\n";
        //Anderson
        if (hall == 1) {
            cout << "1- 101" << "\n";
            cout << "2- 102" << "\n";
            cout << "3- 103" << "\n";
            cout << "4- 104" << "\n";
            cout << "5- 105" << "\n";
            cout << "6- 201" << "\n";
            cout << "7- 203" << "\n";
            cout << "8- 204" << "\n";
            cout << "9- 205" << "\n";
            cout << "10- 301" << "\n";
            cout << "11- 303" << "\n";
            cout << "12- 304" << "\n";
            cout << "13- 305" << "\n";
            //continue with more rooms
            cout << "Please, enter an option: ";
            cin >> room;
        }

        //continue with other halls
    }

    //OFF campus
    else if (on_off == 2) {
        cout << "*** What's the address?\n";
        cin >> offCampusAddress;
    }

    else {
        //system("clear");
        delivery();
    }

}
//*******