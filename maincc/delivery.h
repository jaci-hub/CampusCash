#pragma once
#include <iostream>
#include <string>
#include "file_com_pragmaonce_mysql.h"
#include "orderTotal.h"
#include "formatName.h"
#include "getName_fromTable.h"
#include "listarCoisas.h"
using namespace std;

void delivery() {
    onOffCampus:
    cout << "** Delivery\n";
    cout << "1- ON campus\n";
    cout << "2- OFF campus\n";
    cout << "Please, enter an option: ";
    string onOffChoice, onOffCampus;
    cin >> onOffChoice;
    if (onOffChoice == "1") {
        onOffCampus = "ON campus";
        myOrder.selectedOnOffCampus = "ON campus";
    }
    else if (onOffChoice == "2") {
        onOffCampus = "OFF campus";
        myOrder.selectedOnOffCampus = "OFF campus";
    }
    else goto onOffCampus;

    cout << "** Select a dorm\n";
    dormsList:
    //listar dorms
    onOffCampus = formatName(onOffCampus);
    string onOffCampusDormsTableName = onOffCampus + "DormsTable";
    if (tableExists(onOffCampusDormsTableName)==true)
        listarCoisas("dormID", "dormName", onOffCampusDormsTableName);
    else cout << "* No dorm!\n";
    cout << "b- Back\n";
    cout << "Please, enter an option: ";
    string dormOption;
    cin >> dormOption;

    //heading to roomNums table
    if (isdigit(dormOption[0]) != 0) {
    roomsList:
        //Setting dormName
        string dormName = getName_fromTable(onOffCampusDormsTableName, "dormName", "dormID", dormOption);
        myOrder.selectedDorm = dormName;

        //take out all spaces and lower-case all letters
        dormName = formatName(dormName);

        cout << "* Rooms in " + getName_fromTable(onOffCampusDormsTableName, "dormName", "dormID", dormOption) + "\n";
        //listing dormName table selected
        if (tableExists(onOffCampus + dormName + "RoomNumsTable") == true)
            listarCoisas("roomNumID", "roomNumName", onOffCampus + dormName + "RoomNumsTable");
        else cout << "* No room!\n";
        cout << "b- Back\n";
        cout << "Please, enter an option: ";
        string roomNumOption;
        cin >> roomNumOption;
        if (isdigit(roomNumOption[0]) != 0) {
            myOrder.selectedRoom = getName_fromTable(onOffCampus + dormName + "RoomNumsTable", "roomNumName", "roomNumID", roomNumOption);
        }
        else if (roomNumOption == "b")
            goto roomsList;
    }
    else if (dormOption == "b")
        goto onOffCampus;

    order_total();
}
//*******