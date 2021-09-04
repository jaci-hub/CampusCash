#pragma once
#include <iostream>
#include <string>
#include "classStaff.h"
#include "getStaffSpecificInfo.h"
#include "entregador.h"
using namespace std;

//***Opcoes do menu***
string menuChoice;
void schoolOptionMenu() {
    if (getStaffSpecificInfo(staff.get_email(), "staffType") == "Chef" || getStaffSpecificInfo(staff.get_email(), "staffType") == "Manager") {
        cout << "1- Show Orders\n";
        if (getStaffSpecificInfo(staff.get_email(), "staffType") == "Manager")
            cout << "2- Management\n";
        cout << "e- Log Out\n";
        cout << "Please, enter an option: ";
        cin >> menuChoice;
    }

    if (getStaffSpecificInfo(staff.get_email(), "staffType") == "Entregador") {
        entregador();

        cout << "e- Log Out\n";
        cout << "Please, enter an option: ";
        cin >> menuChoice;
    }
}
//*******